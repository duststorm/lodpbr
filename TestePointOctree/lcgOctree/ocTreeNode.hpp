#ifndef OCTREENODE_HPP_
#define OCTREENODE_HPP_

//[STL container includes]
#include <list>
#include <set>

//[Project includes]
#include "ocTreeRefine.hpp"
#include "ocTreeIterator.hpp"
#include "ocTreeBox.hpp"

//
// Forward declaration of OctreeIterator
//
template <class Real, class ItemPtr, class Refine>
class OctreeIterator;


///
/// An Octree of Pointers to Objects
///
/// @param Real Kernel
/// @param ItemPtr item pointer type to be stored
/// @param Refine refinement criteria
///
template <class Real, class ItemPtr, class Refine = OverflowRefine<Real,ItemPtr> >
class OctreeNode {

  public:

    typedef CGL::Point3<Real>                 			Point3;  ///< A Point in 3D
    typedef CGL::Vector3<Real>                 			Vector3;  ///< A Point in 3D
    typedef Box_3<Real>                                 Box3; ///< Octant box type    
    typedef std::list<ItemPtr>                          ItemPtrList; ///< List of items stored inside leaf nodes
    typedef std::set<ItemPtr>                           ItemPtrSet;   ///< Return type of overlap
    

    friend class OctreeIterator<Real, ItemPtr, Refine>;  ///< Octree iterators are friends
    
    /// Returns a pointer to the octree leaf which contains point p
    /// @param p point which should be inside a descendant leaf
    /// @param world dimensions of this node
    virtual const OctreeNode* searchLeaf (const Box3& world, const Point3& p) const = 0;

    /// Inserts a pointer to an object in this octree node
    /// @param world dimensions of this node
    /// @param level octree level of this node
    /// @param p pointer to object
    /// @param fatherPtr reference to the pointer inside the father which points to this node
    virtual void insert (const Box3& world, int level, const ItemPtr p, OctreeNode*& fatherPtr) = 0;
    
    virtual void split (const Box3& world, int level,OctreeNode*& fatherPtr) = 0;
    
    /// Returns the number of pointers to items inserted into this node
    virtual int itemPtrCount () const = 0;

    /// Returns a set of pointers to objects that overlap a query box
    virtual ItemPtrSet overlap(const Box3& world, const Box3& query) const = 0;

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed 
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @return euclidean distance
    ///
    virtual Real distance (const Box3& world, Real best, const Point3& p) const = 0;

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed 
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @param clsPt Closest point on object.
    /// @return euclidean distance
    ///
    virtual Real distance (const Box3& world, Real best, const Point3& p, Point3& clsPt) const = 0;
    
    /// Returns true or false depending on whether this is a leaf node or not
    virtual bool isLeaf () const = 0;
    
    virtual ItemPtrList itemList () const = 0; 
   
    // Virtual destructor 
    virtual ~OctreeNode(){};
    
   
  
};


#endif /*OCTREENODE_HPP_*/
