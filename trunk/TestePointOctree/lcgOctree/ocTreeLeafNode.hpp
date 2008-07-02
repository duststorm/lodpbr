#ifndef OCTREELEAFNODE_HPP_
#define OCTREELEAFNODE_HPP_

//[STL container includes]
#include <list>
#include <set>
#include <vector>

//[Project includes]
#include "ocTreeNode.hpp"
#include "ocTreeInternalNode.hpp"
#include "ocTreeBox.hpp"
#include "ocTreeIntersection.hpp"

#include "surfels/MergeEllipses.hpp"

// Forward declaration of OctreeIterator
//
template <class Real, class ItemPtr, class Refine>
class OctreeInternalNode;


/// 
/// This represents a leaf octree node. All indexed data (items) are
/// stored herein.
///
template <class Real, class ItemPtr, class Refine = OverflowRefine<Real,ItemPtr> >
class OctreeLeafNode : public OctreeNode<Real, ItemPtr, Refine> {

public:

    typedef OctreeNode<Real, ItemPtr, Refine>  			OctreeNode;          
    typedef OctreeInternalNode<Real, ItemPtr, Refine> 	OctreeInternalNode;
       
    typedef LAL::Vector3<Real> 							Vector3;  ///< A Point in 3D
    typedef LAL::Point3<Real> 							Point3;  ///< A Point in 3D
    typedef Box_3<Real> 								Box3;    ///< Octant box type
    typedef MergeEllipses<Real> 						MergeEllipses;
    
//    friend class OctreeIterator<Real, ItemPtr, Refine>; ///< Octree iterators are friends
    
    typedef std::list<ItemPtr> 							ItemPtrList; ///< List of items stored inside leaf nodes
    typedef std::set<ItemPtr> 							ItemPtrSet;   ///< Return type of overlap
    
    typedef typename std::list<ItemPtr>::iterator 		listItemPtrIterator;
    typedef typename std::list<ItemPtr>::const_iterator const_listItemPtrIterator;
    
    ItemPtrList PtrList; // Pointers to items which overlap this node

    /// constructor
    OctreeLeafNode () {
    	mSurfel = NULL;
    }

    /// destructor
    virtual ~OctreeLeafNode () {
    }

    /// Returns a pointer to the octree leaf which contains point p
    /// @param p point which should be inside a descendant leaf
    /// @param world dimensions of this node
    virtual const OctreeNode* searchLeaf (const Box3& world, const Point3& p) const {
       return this; /// Since we arrived here recursively, this leaf intersects p
    }

    /// inserts a pointer to an object in this octree node
    /// @param world dimensions of this node
    /// @param level octree level of this node
    /// @param p pointer to object
    /// @param fatherPtr reference to the pointer inside the father which points to this node
    virtual void insert (const Box3& world, int level, const ItemPtr p, OctreeNode*& fatherPtr) {

    	mlevel = level;
        PtrList.push_back(p);
     
    }

    virtual void split (const Box3& world, int level, OctreeNode*& fatherPtr) 
    {
        // A maximum of elements, MaxItems, must be declared
        if (Refine::split (world, level, PtrList)) 
        {
        	// Overflow! Redistribute the list
            OctreeInternalNode * newOctreeInternalNode = new OctreeInternalNode ();
            fatherPtr = newOctreeInternalNode;
            newOctreeInternalNode->son[0] = this;
            
            for (int i = 0; i < 8; i++) newOctreeInternalNode->son[i] = new OctreeLeafNode ();
            std::list<ItemPtr> oldPtrList = PtrList;
            
            Point3 m;
            
            // Calcular o Centróide do nó
            for (listItemPtrIterator pi = oldPtrList.begin (); pi != oldPtrList.end(); ++pi)
            {
            	m += (*pi)->Center();
            }
            
            m /= PtrList.size();
            
            newOctreeInternalNode->setMean(m);
            
            PtrList.clear();
            
            // Redistribui os Pontos entre os novos filhos
            for (listItemPtrIterator pi = oldPtrList.begin (); pi != oldPtrList.end(); ++pi) {
                newOctreeInternalNode->insert (world, level + 1, *pi, fatherPtr);
            }
 
            // call split() for sons
            newOctreeInternalNode->split(world,level,fatherPtr);
            
        }
    }
    
    /// Returns the number of pointers to items inserted into this node
    virtual int itemPtrCount () const {
        return PtrList.size();
    }

    /// Returns a set of pointers to objects that overlap or are contained by a query box
    virtual ItemPtrSet overlap(const Box3& world, const Box3& query) const{
      ItemPtrSet leaf_overlap;
      for (const_listItemPtrIterator pi = PtrList.begin (); pi != PtrList.end(); ++pi) {
          if (lcgOctree::checkIntersection(query, *pi)) leaf_overlap.insert(*pi);
      }
        return leaf_overlap;
    }
    
    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed 
    /// @param best best estimate (closest object) found so far
    /// @param world dimensions of this node
    /// @param clsPt Closest point on object.
    /// @return euclidean distance
    ///
    virtual Real distance (const Box3& world, Real best, const Point3& p, Point3& clsPt) const
    {
        Point3 c;
        for (const_listItemPtrIterator pi = PtrList.begin (); pi != PtrList.end(); ++pi)
        {
            Real thisDistance = lcgOctree::distance2Item (*pi, p, c);
            if (fabs(thisDistance) < fabs(best)) 
            {
                best = thisDistance;
                clsPt = c;
            }
        }
        return best;
    }
    
    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed 
    /// @param best best estimate (closest object) found so far
    /// @param world dimensions of this node
    /// @return euclidean distance
    ///
    virtual Real distance (const Box3& world, Real best, const Point3& p) const
    {
        Point3 c;
        return distance (world, best, p, c);
    }
    
    virtual int level () const
    {
    	return mlevel;
    }
     
    
    /// Returns true or false depending on whether this is leaf node or not
    virtual bool isLeaf () const { return true; }
    
    /// FUNCOES CRIADAS POR MIN
    
    virtual Real perpendicularError (Vector3 eye) const
    {
    	return HUGE_VAL;
    }
    
    virtual Real tangencialError (const Vector3& eye) const
    {
    	return HUGE_VAL;
    }
    
    virtual Real geometricError (const Vector3& eye) const
    {
    	return HUGE_VAL;
    }
    
    virtual ItemPtrList itemList () const
    {
    	return PtrList;
    }
    
    // O splat
    virtual ItemPtr surfel() const
    {
    	return NULL;
    }
    
    // Cria novo splat apartir dos pontos da folha
    virtual ItemPtr merge(bool mode) 
    {
    	if (PtrList.size() > 0)
    	{
    		MergeEllipses lMerge = MergeEllipses(PtrList);
    		mSurfel = lMerge.NewPtrSurfel();
    		computeNormalCone();
    	}

    	return NULL;
    }
    // Ver o paper FastMesh - Pajarola e Cone of Normal Eurographics das antigas
    Real normalCone() const
    {
    	if (PtrList.size() > 0) 
    	{
    		return mNormalCone;
    	}
    	
    	return static_cast<Real> (1.0); 	
    }
    
    void computeNormalCone()
    {
    	
    	std::list<Real> lNormaCone;

    	for (const_listItemPtrIterator it = PtrList.begin (); it != PtrList.end(); ++it)
    	{
    		lNormaCone.push_back(mSurfel->Normal() * (*it)->Normal());
    	}

    	mNormalCone = *(std::min_element(lNormaCone.begin(),lNormaCone.end()) );
    	if ( mNormalCone < static_cast<Real>(0) )
    		mNormalCone = static_cast<Real>(1);
    	else
    		mNormalCone = std::sqrt(1.0 - (mNormalCone*mNormalCone)); 
        	

    }
    
    
    
private:
	
	ItemPtr mSurfel;
	int mlevel;
	Real mNormalCone;
	
};


#endif /*OCTREELEAFNODE_HPP_*/
