#ifndef OCTREEINTERNALNODE_HPP_
#define OCTREEINTERNALNODE_HPP_

//[Standart  includes]
#include <cmath>

//[STL includes]
#include <list>
#include <set>
#include <map>

//[Project includes]
#include "ocTreeRefine.hpp"
#include "ocTreeNode.hpp"
#include "ocTreeLeafNode.hpp"

#include "surfels/MergeEllipses.hpp"
#include "slal/Math.hpp"

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
    
    virtual Real NormalCone() const
    {
    	return mNormalCone;	
    }
    
     
    virtual ItemPtr MeanItem() const
    {
    	return mMean;
    }
       
    
    virtual Real TangencialError (const Vector3& eye) const
    {
    	return 1.0;
    }
    
    virtual Real GeometricError (const Vector3& eye) const
    {
    	return 1.0;
    }
    
    virtual ItemPtr Merge(bool mode) 
    {
    	ItemPtrList lLeafSurfel;
    	
        for (int index = 0; index < 8; ++index) 
        {
        	if (son[index]->Merge(mode) != NULL)
        		lLeafSurfel.push_back( son[index]->MeanItem() );
        	
        }
        
        if (lLeafSurfel.size() > 0)
        {
        	MergeEllipses lMerge = MergeEllipses(lLeafSurfel);
    		mMean = lMerge.NewPtrSurfel();
    		
    		ComputePerpendicularError(mode);
    		
        }else
        {
        	mMean = NULL;
        }
        
        
        	
    	return mMean;
    }
    
    void ComputePerpendicularError (bool mode)
        {
        	std::list<Real> lEpMin;
        	std::list<Real> lEpMax;

        	Real epMax = static_cast<Real>(0);
        	Real epMin = static_cast<Real>(0);
        	
        	Real di	   = static_cast<Real>(0);
        	        	        	
        	Real lNormalConeCos = static_cast<Real>(1);
        	Real lNormalConeSin = static_cast<Real>(1);
        	Real lTempCos		= static_cast<Real>(1);
        	
        	if (mode  == true)
        	{
        	
        		for (int index = 0; index < 8; ++index) 
        		{

        			if (son[index]->MeanItem() != NULL)
        			{
        				di = mMean->MajorAxis().first * (std::sqrt(1.0 - (mMean->Normal()*son[index]->MeanItem()->Normal())  ) );


        				epMax = ( ( mMean->Center() - son[index]->MeanItem()->Center() ) * mMean->Normal() + di );
        				epMin =	( ( mMean->Center() - son[index]->MeanItem()->Center() ) * mMean->Normal() - di );
        				
        				lTempCos = son[index]->MeanItem()->Normal() * mMean->Normal();
        				
        				if (lTempCos < lNormalConeCos )
        				{
        					lNormalConeCos = lTempCos;
        					lNormalConeSin = son[index]->NormalCone();
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
        			
        				di = (*it)->Radius() * (std::sqrt(1.0 - (mMean->Normal()*(*it)->Normal() )  ) );


        				epMax = ( ( mMean->Center() - (*it)->Center() ) * mMean->Normal() + di );
        				epMin =	( ( mMean->Center() - (*it)->Center() ) * mMean->Normal() - di );

        				lEpMin.push_back(epMin);
        				lEpMax.push_back(epMax);

        		}

        	}
        		

        	ep = *(std::max_element(lEpMax.begin(),lEpMax.end())) - (*std::min_element(lEpMin.begin(),lEpMin.end())) ;
        	
        	       	       	       	
        	mNormalCone =  std::sqrt(1.0 - (lNormalConeSin*lNormalConeSin)) * lNormalConeCos 
        										-
        				lNormalConeSin * std::sqrt(1.0 - (lNormalConeCos*lNormalConeCos));
        	
        	if ( mNormalCone < static_cast<Real>(0) )
        		mNormalCone = static_cast<Real>(1);
        	else 
        	   	mNormalCone = std::sqrt(1.0 - (mNormalCone*mNormalCone));
        	
        	
        }
          
            
        // Por que passando como const VEctor3& eye , da error de disqualified  ....
        
        virtual Real PerpendicularError (Vector3 eye) const
        {
        	
        	if (mMean != NULL) 
        	{
        		Real cos = mMean->Normal().norm() * eye.norm();
        	
        		Real ImageError = (ep*(1- cos*cos))/eye.length();
        	
        		return ImageError;
        	}
        	
        	return HUGE_VAL;
        }
    
private:
	
	  Point3 	mean_;
	  ItemPtr 	mMean;
	  
	  int 		mlevel;
	  
	  Real ep;
	  Real mNormalCone;
};


#endif /*OCTREEINTERNALNODE_HPP_*/
