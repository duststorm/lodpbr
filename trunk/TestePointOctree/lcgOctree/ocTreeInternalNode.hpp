#ifndef OCTREEINTERNALNODE_HPP_
#define OCTREEINTERNALNODE_HPP_

//[Standart  includes]
#include <cmath>

//[STL includes]
#include <list>
#include <set>
#include <map>
#include <GL/gl.h> 

//[Project includes]
#include "ocTreeRefine.hpp"
#include "ocTreeNode.hpp"
#include "ocTreeLeafNode.hpp"

#include "surfels/MergeEllipses.hpp"
#include "slal/Math.hpp"
#include "Scene/Camera.hpp"

///
/// This represents an internal Octree Node. These point to eight 
/// son nodes each.
///
template <class Real, class ItemPtr, class Refine = OverflowRefine<Real,ItemPtr> >
class OctreeInternalNode : public OctreeNode<Real, ItemPtr, Refine> {

    typedef OctreeNode<Real, ItemPtr, Refine> OctreeNode;      

    typedef  LAL::Point3<Real>   Point3;  ///< A Point in 3D
    typedef  LAL::Vector3<Real>  Vector3;  ///< A Point in 3D
    typedef  MergeEllipses<Real> MergeEllipses; 
    
    typedef Box_3<Real> Box3; ///< Octant box type
    typedef std::list<ItemPtr> ItemPtrList; ///< List of items stored inside leaf nodes
    typedef std::set<ItemPtr> ItemPtrSet;   ///< Return type of overlap
    typedef typename std::set<ItemPtr>::iterator ItemPtrSetIterator;
    typedef typename std::list<ItemPtr>::iterator ItemPtrListIterator;
    typedef typename std::list<ItemPtr>::iterator 		listItemPtrIterator;
       
    friend class OctreeLeafNode<Real, ItemPtr, Refine>; ///< Leaf nodes are friends
    friend class OctreeIterator<Real, ItemPtr, Refine>; ///< Octree iterators are friends
    
public:
	
	OctreeNode* son[8];

	virtual void setMean ( const Point3& m)
	{
		this->mean_ = m;
	}
	
	virtual Point3 mean () const
	{
		return this->mean_;
	}
	
	/// constructor
    OctreeInternalNode () {
       son [0] = son [1] = son [2] = son [3] =
       son [4] = son [5] = son [6] = son [7] = 0;
       mSurfel = NULL;
    }

    /// destructor
    virtual ~OctreeInternalNode () {
        for (int i = 0; i < 8; i++) {
             if (son [i]!= 0) delete son [i];
        }
    }

    /// Returns a pointer to the octree leaf which contains point p
    /// @param p point which should be inside a descendant leaf
    /// @param world dimensions of this node
    virtual const OctreeNode* searchLeaf (const Box3& world, const Point3& p) const {
        int mult = 1;
        int index = 0;
        Real min[3], max[3];
        Point3 p1 (world.xmin(),world.ymin(),world.zmin());
        Point3 p2 (world.xmax(),world.ymax(),world.zmax());
        for (int d = 0; d < 3; ++d) {
            Real middle = mean_[d];
            if ((p[d]) > middle) {
                index += mult;
                min[d] = middle; max[d] = (p2[d]);
            } else {
                max[d] = middle; min[d] = (p1[d]);
            }
            mult *= 2;
        }
        return son[index]->searchLeaf (Box3 (Point3(min[0], min[1], min[2]), 
                                             Point3(max[0], max[1], max[2])), p);
    }

    /// inserts a pointer to an object in this octree node
    /// @param world dimensions of this node
    /// @param level octree level of this node
    /// @param p pointer to object
    /// @param fatherPtr reference to the pointer inside the father which points to this node
    virtual void insert (const Box3& world, int level, const ItemPtr p, OctreeNode*& fatherPtr) {

    	mlevel = level;
    	
        for (int index = 0; index < 8; ++index) {
            Box3 suboctant = world.coords(index,mean_);
            
            // It is necessary to define a method do_intersect (Box_3, Item)
            if (lcgOctree::checkIntersection(suboctant, p))
            {
              	son[index]->insert(suboctant, level+1, p, son[index]);
            }
            
            
        }
    }

    
    virtual void split (const Box3& world, int level, OctreeNode*& fatherPtr) 
    {
        for (int index = 0; index < 8; ++index) {
        	Box3 suboctant = world.coords(index,mean_);
        	son[index]->split(suboctant,level + 1,son[index]);
        }
    }
    
    
    /// Returns the number of pointers to items inserted into this node
    virtual int itemPtrCount () const {
        int sum = 0;
        for (int i = 0; i < 8; ++i) sum += son[i]->itemPtrCount ();
        return sum;
    }

    /// Returns a set of pointers to objects that overlap a query box
    virtual ItemPtrSet overlap(const Box3& world, const Box3& query) const {
        ItemPtrSet internal_overlap;

        for (int index = 0; index < 8; ++index) {
           Box3 suboctant = world.coords(index,mean_);

           // do_intersect must be overloaded to support also
           // the box2box check.
           ItemPtrSet temp_overlap;
           if (suboctant.intersect(query)){
               temp_overlap = son[index]->overlap(suboctant, query);
           }
           if (!temp_overlap.empty()){
               for (ItemPtrSetIterator pi = temp_overlap.begin (); pi != temp_overlap.end(); ++pi){
                   internal_overlap.insert(*pi);
               }
           }  
       }

       return internal_overlap;
    }
        
    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @param p Point in relation to which the distance will be computed 
    /// @return euclidean distance
    ///
    virtual Real distance (const Box3& world, Real best, const Point3& p) const
    {
        Point3 c;
        return distance (world, best, p, c);
    }

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @param p Point in relation to which the distance will be computed 
    /// @param clsPt closest point  
    /// @return euclidean distance
    ///
    virtual Real distance (const Box3& world, Real best, const Point3& p, Point3& clsPt) const
    {
    	typedef typename std::less<Real> lessReal;
    	typedef std::multimap <Real, int, lessReal > multimapReal;
        typedef typename std::multimap <Real, int, lessReal >::iterator multimapRealIterator;
        
        multimapReal iSon;
        
        for (int i = 0; i < 8; ++i)
        { 
            iSon.insert (std::pair <Real, int> (world.coords(i,mean_).distance(p), i));
        }
        for (multimapRealIterator j = iSon.begin (); j != iSon.end(); ++j)
        {
            Real boxDist = j->first;
            if (fabs(boxDist) > fabs(best)) break;
            int sonIndex = j->second;
            Real currentDist = son[sonIndex]->distance (world.coords (sonIndex,mean_),  best, p, clsPt);
            if (fabs(currentDist) < fabs(best))
            {
                best = currentDist;
            }
        }
        return best;
    }   
    
    /// Returns true or false depending on whether this is leaf node or not
    virtual bool isLeaf () const { return false; }
    
    
    /// FUNCOES QUE EU CRIEI Otimizar isso
    
    virtual ItemPtrList itemList () const
    {
    	ItemPtrList  leafList;
    	
    	for (int sonIndex = 0; sonIndex < 8 ; ++sonIndex)
    	{
    		ItemPtrList  temp_Leaf = son[sonIndex]->itemList();
    		
    		if (!temp_Leaf.empty()){
    			for (ItemPtrListIterator pi = temp_Leaf.begin (); pi != temp_Leaf.end(); ++pi){
    				leafList.push_back(*pi);
    			}
    		}  
    		
    	}
    	
    	return leafList;
    }
    
    virtual int level () const
    {
    	return mlevel;
    }
    
    virtual Real normalCone() const
    {
    	return mNormalCone;	
    }
    
     
    virtual ItemPtr surfel() const
    {
    	return mSurfel;
    }
       
    
    
    // Por que passando como const VEctor3& eye , da error de disqualified  ....
    // Paper Sequential Point Trees
    virtual Real perpendicularError (Vector3& eye) const
    {
    	
    	if (mSurfel != NULL) 
    	{
//    		Real cos = mSurfel->Normal().Norm() * eye.Norm();
//    	
//    		Real ImageError = (ep*std::sqrt(1- cos*cos))/eye.Length();
//    	
//    		return ImageError;
    	}
    	
    	return HUGE_VAL;
    }
    // Paper Sequential Point Trees
    virtual Real tangencialError (const Vector3& eye) const
    {
    	return HUGE_VAL;
    }
    // Será a junção dos dois erros anteriores
    virtual Real geometricError (Vector3& eye) const
    {
    	
    	return (mGeometricError/eye.Length());
    	
    }
    
    Real ComputeTangencialError (MergeEllipses &Merge)
    {
    	LAL::Camera camera;
    	Real et;
    	
    	camera.SetUp(Merge.MinorAxis().second);
    	camera.SetPosition(LAL::Vector3<float>(Merge.Center().x,Merge.Center().y,Merge.Center().z));
    	camera.SetEyes(LAL::Vector3<float>(Merge.Center().x,Merge.Center().y,Merge.Center().z)+(-Merge.Normal()*1.0f));
   	
    	
        glViewport(0, 0, 32, 32);
        camera.SetWindowSize(32,32);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        camera.SetProjectionMatrix(-Merge.MajorAxis().first,Merge.MajorAxis().first,-Merge.MinorAxis().first,Merge.MinorAxis().first,-100.0f,100.0f);
        glLoadMatrixf((~camera.OrthographicProjectionMatrix()).ToRealPtr());
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
         
        glMultMatrixf((~camera.ViewMatrixNormal()).ToRealPtr());
              
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawBuffer(GL_BACK);
        glDisable(GL_DEPTH_TEST);
        
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_TRIANGLE_FAN);
        	Merge.NewSurfel().draw(8);
        glEnd();
        
        glColor3f(0.0,1.0,0.0);
    	int cont = 0;
    	typename std::list<Point3* >::iterator it;
        for( it = Merge.mProjectedPoint.begin(); it != Merge.mProjectedPoint.end(); ++it  )
        {
        	if ( (cont % 8) == 0)
        		glBegin(GL_TRIANGLE_FAN);
        			glVertex3fv(  (*it)->ToRealPtr()  );
        			
        		cont++;		
        	if ( (cont % 8) == 0)
        		glEnd();
        	       	
        }
        
        glFlush();
        glEnable(GL_DEPTH_TEST);
        GLfloat *outputBuffer = new GLfloat[32 * 32 * 4];
        glReadBuffer(GL_BACK);
        glReadPixels(0, 0, 32, 32, GL_RGBA, GL_FLOAT, &outputBuffer[0]);
                
        float red   = 0.0f;
        float green = 0.0f;
        
        for (int i = 0; i < 4096; i+=4) 
        {
            red   += outputBuffer[i + 0];
            green += outputBuffer[i + 1];            	                  
        }
        
        delete[] outputBuffer;
        
//        std::cout << "red " << red << std::endl;
//        std::cout << "green " << green << std::endl;
//        std::cout << " P " << 100.f*(green/(green+red)) << "%" << std::endl;
        
        et = static_cast<Real> ( 1- (green/(green+red)) );
        
        return ( et );
    }

    Real ComputePerpendicularError (bool mode)
    {
    	std::list<Real> lEpMin;
    	std::list<Real> lEpMax;

    	Real epMax 			= static_cast<Real>(0);
    	Real epMin 			= static_cast<Real>(0);

    	Real di	   			= static_cast<Real>(0);
    	Real ep				= static_cast<Real>(0);  
    	
    	Real lNormalConeCos = static_cast<Real>(1);
    	Real lNormalConeSin = static_cast<Real>(1);
    	Real lTempCos		= static_cast<Real>(1);

    	Vector3 n  = mSurfel->Normal();

    	if (mode  == true)
    	{

    		for (int index = 0; index < 8; ++index) 
    		{

    			if (son[index]->surfel() != NULL)
    			{

    				Vector3 ni = son[index]->surfel()->Normal();

    				di = mSurfel->MajorAxis().first * ( std::sqrt(1.0 - (n*ni) * (n*ni)  ) );

    				epMax = ( ( mSurfel->Center() - son[index]->surfel()->Center() ) * n + di );
    				epMin =	( ( mSurfel->Center() - son[index]->surfel()->Center() ) * n - di );

    				lTempCos = ni * n;

    				if (lTempCos < lNormalConeCos )
    				{
    					lNormalConeCos = lTempCos;
    					lNormalConeSin = son[index]->normalCone();
    				}

    				lEpMin.push_back(epMin);
    				lEpMax.push_back(epMax);

    			}

    		}

    	}else
    	{

    		ItemPtrList lp = this->itemList();

    		for (listItemPtrIterator it = lp.begin (); it != lp.end(); ++it)
    		{

    			di = (*it)->MajorAxis().first * (std::sqrt(1.0 - (n*(*it)->Normal() ) * (n*(*it)->Normal() )  ) );

    			epMax = ( ( mSurfel->Center() - (*it)->Center() ) * n + di );
    			epMin =	( ( mSurfel->Center() - (*it)->Center() ) * n - di );

    			lEpMin.push_back(epMin);
    			lEpMax.push_back(epMax);

    		}

    	}


    	ep = *(std::max_element(lEpMax.begin(),lEpMax.end())) - (*std::min_element(lEpMin.begin(),lEpMin.end())) ;


    	mNormalCone =  std::sqrt(1.0 - (lNormalConeSin*lNormalConeSin)) * lNormalConeCos -
    				   lNormalConeSin * std::sqrt(1.0 - (lNormalConeCos*lNormalConeCos));

    	if ( mNormalCone < static_cast<Real>(0) )
    		mNormalCone = static_cast<Real>(1);
    	else 
    		mNormalCone = std::sqrt(1.0 - (mNormalCone*mNormalCone));

    	return ( ep );
    }
            

    
    // Juntas os oitos filhos (se tiver) usando técnica L21 do Progressive Splatting
    virtual ItemPtr merge(bool mode) 
    {
    	ItemPtrList lLeafSurfel;
       	
    	if ( mode == true)
    	{

    		for (int index = 0; index < 8; ++index) 
    		{
    			if (son[index]->merge(mode) != NULL)
    			{
    				lLeafSurfel.push_back( son[index]->surfel() );
    			}
    			else
    			{
    		   		ItemPtrList  temp_Leaf = son[index]->itemList();
    		    		
    		    		if (!temp_Leaf.empty()){
    		    			for (ItemPtrListIterator pi = temp_Leaf.begin (); pi != temp_Leaf.end(); ++pi){
    		    				lLeafSurfel.push_back(*pi);
    		    			}
    		    		}  
    			}
    				
    		}

    	}else
    	{
    		for (int index = 0; index < 8; ++index) 
    		{
    			son[index]->merge(mode); 

    		}
    		
	   		lLeafSurfel = this->itemList();
     	}
            	   	
        if (lLeafSurfel.size() > 0)
        {
        	MergeEllipses lMerge = MergeEllipses(lLeafSurfel);
    		mSurfel = lMerge.NewPtrSurfel();
    		
    		Real ep,et;
    		
    		ep = ComputePerpendicularError(mode);
    		et = ComputeTangencialError(lMerge);
    		
    		mGeometricError = std::sqrt( (ep*ep) + (et*et) ); 
    			
        }else
        {
        	mSurfel = NULL;
        }
               
        	
    	return mSurfel;
    }
    
      
private:
	
	  Point3 	mean_;
	  ItemPtr 	mSurfel;
	  
	  int 		mlevel;
	  
	  Real mGeometricError;
	  
	  Real mNormalCone;
};


#endif /*OCTREEINTERNALNODE_HPP_*/

