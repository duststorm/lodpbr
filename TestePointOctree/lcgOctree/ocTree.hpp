#ifndef __OCTREE__
#define __OCTREE__

//[Numeric includes]
#include <cmath>
#include <numeric>

//[STL container includes]
#include <list>
#include <set>
#include <map>

//[Project includes]
#include "ocTreeInternalNode.hpp"
#include "ocTreeLeafNode.hpp"
#include "ocTreeNode.hpp"

using namespace std;


/** Base class for an octree data structure.
 *	@author <A HREF="mailto:esperanc@lcg.ufrj.br">Claudio Esperanca</a> and
 *	<A HREF="mailto:roma@lcg.ufrj.br">Paulo Roma Cavalcanti</a>
 *	@version $Revision: 1.20 $ $Date: 2004/05/01 19:21:21 $
 *	
 * This is the octree data structure most users will actually use.
 * Nodes ares split based on a given refinement criterion.
 * Default criterion is based on occupancy only.
 *
 * @param Real Which CGAL Kernel to use
 * @param ItemPtr The octree will store pointers of this type
 * @param Refine given criterion.
 *
 */
template <class Real, class ItemPtr, class Refine = OverflowRefine<Real,ItemPtr> >
class Octree {

public:
    typedef typename CGL::Point3<Real> 			Point3;     ///< A Point in 3D
    typedef Box_3<Real> 						Box3;       ///< Octant extent
    typedef list<ItemPtr> 						ItemPtrList;///< What is actually stored in a leaf
    typedef set<ItemPtr> 						ItemPtrSet; ///< Return type of overlap
    typedef OctreeIterator<Real,ItemPtr,Refine> Iterator;   ///< Octree pre-order iterator
    
  protected:
    ///
    /// World covered by this octree
    ///
    Box3 world;
    
    ///
    /// Main OctreeNode pointer
    ///
    

public :
	OctreeNode<Real, ItemPtr, Refine> * root;
    /// Main Constructor
    /// @param theWorld extent of the world covered by the octree
    Octree() : world (Box3(Point3(-1,-1,-1), Point3(1,1,1))), root (0){
    };
    
    Octree (const Box3& theWorld) : world (theWorld), root (0) {
       root = new OctreeLeafNode<Real, ItemPtr, Refine>;
    }
   
    /// destructor. 
    virtual ~Octree() {}
         
    /// inserts a pointer to an object in this octree
    /// @param p pointer to object
    virtual void insert (const ItemPtr p) {
         root->insert (world, 0, p, root);
    }                   

    void split () 
    {
    	root->split(world, 0,root);
    }
    
    void Merge ()
    {
    	root->Merge();
    }
    
    /// Returns the number of pointers to items inserted into this octree
    virtual int itemPtrCount () const {
      return root->itemPtrCount();
    }

    /// Returns all items that overlap a given box  
    /// @param query query box
    ItemPtrSet overlap (const Box3 query) const {
       return root->overlap (world, query);
    }

    /// Returns a pre-order iterator to the octree
    Iterator begin () {
        return Iterator (root);
    }
    
    Box3 world_()  const
    {
    	return world;	
    }
    
    
    /// Returns an iterator to past the end of the octree
    Iterator end () {
        return Iterator ();
    }
    
    /// Returns the box geometry of an octree node pointed to by an iterator
    Box3 box (const Iterator& i) const {
     
        Real x0, y0, z0, x1, y1, z1;
        
        i.coords (world, x0, y0, z0, x1, y1, z1);
        
        Point3 minCorner (x0, y0, z0);
        Point3 maxCorner (x1, y1, z1);
        
        return Box3 (minCorner, maxCorner);
    }
    
    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed 
    /// @return euclidean distance
    ///
    Real distance (const Point3& p) const
    {
        return root->distance (world, HUGE_VAL, p);
    }
    
    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed 
    /// @param clsPt Closest point on object.
    /// @return euclidean distance
    ///
    Real distance (const Point3& p, Point3& clsPt) const
    {
        return root->distance (world, HUGE_VAL, p, clsPt);
    }
    
};

#endif
