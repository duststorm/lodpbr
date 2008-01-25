/*
**	octree.h - implements an octree data structure.
**

  Program:   trgl
  Module:    $RCSfile: octree.h,v $
  Language:  C++
  Date:      $Date: 2004/04/29 11:10:17 $
  Version:   $Revision: 1.19 $

**      Created: Apr 21 2004.
**	
**	purpose:  To allow a fast implementation of a distance function from
**                a point to a cgcModel.
*/

#ifndef __OCTREE__
#define __OCTREE__

//#include "cgaltypes.h"
#include "octreeBox.h"
#include "octreeIntersection.h"

#include <list>
#include <set>
#include <map>

using namespace std;

class TPInterpolation;

///
/// Refinement criteria for octrees
///
template <class K, class ItemPtr>
struct OctreeRefine {
    ///
    /// Decides whether or not to split a leaf node
    /// @param world space of the node octant
    /// @param level node level
    /// @param items list of items inside the leaf node
    static bool split (const Box_3<K>& world, int level, const list<ItemPtr>& items) {
        return false;
    }
};

///
/// A Simple Refinement Criteria for leaf nodes based on occupancy.
/// A node is refined whenever it holds more than "Max" items, and
/// the subdivision level has not reached "LevelMax".
///
template <class K, class ItemPtr, int Max=1, int LevelMax = 5>
struct OverflowRefine : public OctreeRefine <K, ItemPtr> {
//	static int Max;
//    static int LevelMax;

    ///
    /// Split a leaf node iff the list contains more than Max items
    /// @param world space of the node octant
    /// @param level node level
    /// @param items list of items inside the leaf node
    static bool split (const Box_3<K>& world, int level, const list<ItemPtr>& items) {
        return items.size() > Max && level < LevelMax;
    }
};
///
/// A Simple Refinement Criteria for leaf nodes based on occupancy.
/// A node is refined whenever it holds more than "Max" items, and
/// the subdivision level has not reached "LevelMax".
///

template <class K, class ItemPtr>
struct VarOverflowRefine : public OctreeRefine <K, ItemPtr> {
	static int Max;
	static int LevelMax;

    ///
    /// Split a leaf node iff the list contains more than Max items
    /// @param world space of the node octant
    /// @param level node level
    /// @param items list of items inside the leaf node
    static bool split (const Box_3<K>& world, int level, const list<ItemPtr>& items) {
        return items.size() > Max && level < LevelMax;
    }
};

//
// Forward declaration of OctreeIterator
//
template <class K, class ItemPtr, class Refine>
class OctreeIterator;


///
/// An Octree of Pointers to Objects
///
/// @param K Kernel
/// @param ItemPtr item pointer type to be stored
/// @param Refine refinement criteria
///
template <class K, class ItemPtr, class Refine = VarOverflowRefine<K,ItemPtr> >
class OctreeNode {

  public:
    typedef typename CGAL::Point_3<K> Point3;  ///< A Point in 3D
    typedef Box_3<K> Box3; ///< Octant box type
    friend class OctreeIterator<K, ItemPtr, Refine>; ///< Octree iterators are friends
    typedef list<ItemPtr> ItemPtrList; ///< List of items stored inside leaf nodes
    typedef set<ItemPtr> ItemPtrSet;   ///< Return type of overlap

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


    /// Returns the number of pointers to items inserted into this node
    virtual int itemPtrCount () const = 0;


    virtual ItemPtr getItem (int id) const = 0;


    virtual void setRBF (TPInterpolation* rbfPtr) = 0;


    virtual  TPInterpolation* getRBF (void) const = 0;

    /// Returns a set of pointers to objects that overlap a query box
    virtual ItemPtrSet overlap(const Box3& world, const Box3& query) const = 0;

    /// Returns a set of pointers to objects that overlap a query sphere
    virtual ItemPtrSet overlap(const Box3& world, const Sphere3& query) const = 0;

    /// Returns a set of pointers to functions that overlap a query sphere
    virtual ItemPtrSet overlapfunc(const Box3& world, const Sphere3& query) const = 0;

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @return euclidean distance
    ///
    virtual double distance (const Box3& world, double best, const Point3& p) const = 0;

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @param clsPt Closest point on object.
    /// @return euclidean distance
    ///
    virtual double distance (const Box3& world, double best, const Point3& p, Point3& clsPt) const = 0;

    /// Returns true or false depending on whether this is a leaf node or not
    virtual bool isLeaf () const = 0;
};

// This is a forward declaration of OctreeLeafNode so that we may refer to
// it in OctreeInternalNode as a friend class
template <class K, class ItemPtr, class Refine>
class OctreeLeafNode;

///
/// This represents an internal Octree Node. These point to eight
/// son nodes each.
///
template <class K, class ItemPtr, class Refine = OverflowRefine<K,ItemPtr> >
class OctreeInternalNode : public OctreeNode<K, ItemPtr, Refine> {

    typedef OctreeNode<K, ItemPtr, Refine> OctreeNode;

    typedef typename CGAL::Point_3<K> Point3;  ///< A Point in 3D
    typedef Box_3<K> Box3; ///< Octant box type
    typedef list<ItemPtr> ItemPtrList; ///< List of items stored inside leaf nodes
    typedef set<ItemPtr> ItemPtrSet;   ///< Return type of overlap
    typedef typename set<ItemPtr>::iterator ItemPtrSetIterator;

    OctreeNode* son[8];

    friend class OctreeLeafNode<K, ItemPtr, Refine>; ///< Leaf nodes are friends
    friend class OctreeIterator<K, ItemPtr, Refine>; ///< Octree iterators are friends

public:

    /// constructor
    OctreeInternalNode () {
       son [0] = son [1] = son [2] = son [3] =
       son [4] = son [5] = son [6] = son [7] = 0;
       //box = b;
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
        double min[3], max [3];
        for (int d = 0; d < 3; d++) {
            double middle = (world.max()[d] + world.min()[d]) / 2;
            if (p [d] > middle) {
                index += mult;
                min [d] = middle; max [d] = world.max()[d];
            } else {
                max [d] = middle; min [d] = world.min()[d];
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

        for (int index = 0; index < 8; ++index) {
            Box3 suboctant = world.coords(index);

            // It is necessary to define a method do_intersect (Box_3, Item)
            if (lcgOctree::checkIntersection(suboctant, p))
            {
                son[index]->insert(suboctant, level+1, p, son[index]);
            }
        }
    }

    /// Returns the number of pointers to items inserted into this node
    virtual int itemPtrCount () const {
        int sum = 0;
        for (int i = 0; i < 8; ++i) sum += son[i]->itemPtrCount ();
        return sum;
    }

    virtual ItemPtr getItem (int id) const {
		return 0;
    }

    virtual void setRBF (TPInterpolation* rbfPtr){}
    virtual  TPInterpolation* getRBF (void) const{
    	return 0;
    }


    /// Returns a set of pointers to objects that overlap a query box
    /// @param world box of current node
    /// @param query query box
    /// @return set of pointers to objects that overlap query
    virtual ItemPtrSet overlap(const Box3& world, const Box3& query) const {
        ItemPtrSet internal_overlap;

        for (int index = 0; index < 8; ++index) {

           // Compute the box of suboctant 'index'
           Box3 suboctant = world.coords(index);

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


    /// Returns a set of pointers to objects that overlap a query box
    /// @param world box of current node
    /// @param query query sphere
    /// @return set of pointers to objects that overlap query
    virtual ItemPtrSet overlap(const Box3& world, const Sphere3& query) const {
        ItemPtrSet internal_overlap;

        for (int index = 0; index < 8; ++index) {

           // Compute the box of suboctant 'index'
           Box3 suboctant = world.coords(index);

           // do_intersect must be overloaded to support also
           // the box2box check.
           ItemPtrSet temp_overlap;

           if (lcgOctree::checkIntersection (query, suboctant)){
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


    /// Returns a set of pointers to functions that overlap a query box
    /// @param world box of current node
    /// @param query query sphere
    /// @return set of pointers to objects that overlap query
    virtual ItemPtrSet overlapfunc(const Box3& world, const Sphere3& query) const {
        ItemPtrSet internal_overlapfunc;

        for (int index = 0; index < 8; ++index) {

           // Compute the box of suboctant 'index'
           Box3 suboctant = world.coords(index);

           // do_intersect must be overloaded to support also
           // the box2box check.
           ItemPtrSet temp_overlapfunc;

           if (lcgOctree::checkIntersection (query, suboctant))
               temp_overlapfunc = son[index]->overlapfunc(suboctant, query);

           if (!temp_overlapfunc.empty())
               internal_overlapfunc.insert(rbfPtr);




       return internal_overlapfunc;
    }


    //
    //


    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param world dimensions of this node
    /// @param best best estimate (closest object) found so far
    /// @param p Point in relation to which the distance will be computed
    /// @return euclidean distance
    ///
    virtual double distance (const Box3& world, double best, const Point3& p) const
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
    virtual double distance (const Box3& world, double best, const Point3& p, Point3& clsPt) const
    {
        multimap <double, int, std::less<double> > iSon;
        for (int i = 0; i < 8; ++i)
        {
            iSon.insert (pair <double, int> (world.coords(i).distance(p), i));
        }
        for (multimap <double, int, std::less<double> >::iterator j = iSon.begin (); j != iSon.end(); ++j)
        {
            double boxDist = j->first;
            if (boxDist > best) break;
            int sonIndex = j->second;
            double currentDist = son[sonIndex]->distance (world.coords (sonIndex),  best, p, clsPt);
            if (currentDist < best)
            {
                best = currentDist;
            }
        }
        return best;
    }
    
    /// Returns true or false depending on whether this is leaf node or not
    virtual bool isLeaf () const { return false; }

};

///
/// This represents a leaf octree node. All indexed data (items) are
/// stored herein.
///
template <class K, class ItemPtr, class Refine = OverflowRefine<K,ItemPtr> >
class OctreeLeafNode : public OctreeNode<K, ItemPtr, Refine> {

  public:

    typedef OctreeNode<K, ItemPtr, Refine> OctreeNode;
    typedef OctreeInternalNode<K, ItemPtr, Refine> OctreeInternalNode;

    typedef typename CGAL::Point_3<K> Point3;  ///< A Point in 3D
    typedef Box_3<K> Box3; ///< Octant box type
//    friend class OctreeIterator<K, ItemPtr, Refine>; ///< Octree iterators are friends
    typedef list<ItemPtr> ItemPtrList; ///< List of items stored inside leaf nodes
    typedef set<ItemPtr> ItemPtrSet;   ///< Return type of overlap

    typedef typename list<ItemPtr>::iterator listItemPtrIterator;
    typedef typename list<ItemPtr>::const_iterator const_listItemPtrIterator;

    list<ItemPtr> PtrList; // Pointers to items which overlap this node
	TPInterpolation* rbf;

    /// constructor
    OctreeLeafNode () {
    	//box = b;
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

        PtrList.push_back(p);

        // A maximum of elements, getItemMaxItems, must be declared
        if (Refine::split (world, level, PtrList)) {
            // Overflow! Redistribute the list
            OctreeInternalNode * newOctreeInternalNode = new OctreeInternalNode ();
            fatherPtr = newOctreeInternalNode;
            newOctreeInternalNode->son[0] = this;
            for (int i = 1; i < 8; i++) newOctreeInternalNode->son[i] = new OctreeLeafNode ();
            list<ItemPtr> oldPtrList = PtrList;
            PtrList.clear();
            for (listItemPtrIterator pi = oldPtrList.begin (); pi != oldPtrList.end(); ++pi) {
                newOctreeInternalNode->insert (world, level + 1, *pi, fatherPtr);
            }
        }
    }

    /// Returns the number of pointers to items inserted into this node
    virtual int itemPtrCount () const {
        return PtrList.size();
    }

    virtual void setRBF (TPInterpolation* rbfPtr){
    	rbf = rbfPtr;
    }

    virtual  TPInterpolation* getRBF (void) const{
    	return rbf;
    }

	virtual ItemPtr getItem (int id) const {
		int i = 0;
		for (const_listItemPtrIterator li = PtrList.begin(); li != PtrList.end(); ++li, ++i)
        	if (i == id){
				return *li;
            }
        cout<<"0"<<endl;
        return 0;
    }

    /// Returns a set of pointers to objects that overlap a query box
    virtual ItemPtrSet overlap(const Box3& world, const Box3& query) const{
      ItemPtrSet leaf_overlap;
      for (const_listItemPtrIterator pi = PtrList.begin (); pi != PtrList.end(); ++pi) {
          if (lcgOctree::checkIntersection(query, *pi)) leaf_overlap.insert(*pi);
      }
        return leaf_overlap;
    }

	/// Returns a set of pointers to objects that overlap a query sphere
    virtual ItemPtrSet overlap(const Box3& world, const Sphere3& query) const{
      ItemPtrSet leaf_overlap;
      for (const_listItemPtrIterator pi = PtrList.begin (); pi != PtrList.end(); ++pi) {
          if (lcgOctree::checkIntersection(query, *pi)) leaf_overlap.insert(*pi);
      }
        return leaf_overlap;
    }

    /// Returns a set of pointers to functions that overlap a query sphere
    virtual ItemPtrSet overlapfunc(const Box3& world, const Sphere3& query) const{
      ItemPtrSet leaf_overlapfunc;
      if (lcgOctree::checkIntersection(query, world)) leaf_overlapfunc.insert(rbfPtr);

        return leaf_overlapfunc;
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
    virtual double distance (const Box3& world, double best, const Point3& p, Point3& clsPt) const
    {
        Point3 c;
        for (const_listItemPtrIterator pi = PtrList.begin (); pi != PtrList.end(); ++pi)
        {
            double thisDistance = lcgOctree::distance2Item (*pi, p, c);
            if (thisDistance < best)
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
    virtual double distance (const Box3& world, double best, const Point3& p) const
    {
        Point3 c;
        return distance (world, best, p, c);
    }
    
    /// Returns true or false depending on whether this is leaf node or not
    virtual bool isLeaf () const { return true; }
};

#define debug(msg) // cout << msg << endl

///
/// Octree Iterator
///
template <class K, class ItemPtr, class Refine = OverflowRefine<K,ItemPtr> >
class OctreeIterator {
    
    typedef OctreeNode<K, ItemPtr, Refine> Node; ///< Octree Node
    typedef OctreeInternalNode<K, ItemPtr, Refine> InternalNode; ///< Internal OctreeNode
    typedef Node* NodePtr; ///< Pointer to octree node
    
    vector<NodePtr*> path; ///< Path from root to pointed node
    int pathLen; ///< Path length
    NodePtr root; ///< Root of octree

public:
    
    /// Default constructor: null pointer
    OctreeIterator () : pathLen (-1), root(0) {};
    
    /// Constructor from a pointer to an octree node
    OctreeIterator (NodePtr r) : pathLen(0), root(r) {};
    
    /// Constructor from another iterator
    OctreeIterator (const OctreeIterator& i) {
        path = i.path;
        pathLen = i.pathLen;
        root = i.root;
    }
    
    /// Tells when an iterator cannot be dereferenced
    bool null () const { return root == 0 || pathLen < 0; }
    
    /// Level of the node inside the octree (Root is level 0)
    int level () const { return pathLen; }

    /// Pointer to father node. Pre-condition: node is not root.
    InternalNode * father () const {
        assert (pathLen > 0);
        if (pathLen == 1)
            return (InternalNode*) root;
        else 
            return (InternalNode*) (*path [pathLen-2]);
    }

    /// Which son of its father is this node. Pre-condition: node is not root
    int sonIndex () const {
        int ison = path [pathLen-1] - father()->son;
        assert (ison >=0 && ison < 8);
        return ison;
    }
    
    /// Returns in x,y,z the coordinates of the minimum corner of the
    /// box occupied by the node. The root node is assumed to be of size
    /// 1 and have min coords = (0,0,0)
    void minCoords (double& x, double& y, double& z) const {
        double sz = 1.0;
        x = y = z = 0.0;
        InternalNode* fatherNode = (InternalNode*) root;
        for (int i = 0; i < pathLen; ++i) {
            sz /= 2;
            int ison = path [i] - fatherNode->son;
            assert (ison >= 0 && ison < 8);
            if (ison & 1) x += sz;
            if (ison & 2) y += sz;
            if (ison & 4) z += sz;
            fatherNode = (InternalNode*) (*path [i]);
        }
    }
    
    /// Equality predicate
    bool operator== (const OctreeIterator& i) const {
        return null() && i.null() ||
               !null() && !i.null() && operator* () == *i;
    }

    /// Inequality predicate
    bool operator!= (const OctreeIterator& i) const {
        return ! operator== (i);
    }

    /// Dereferences an iterator
    NodePtr operator* () const {
        assert (!null());
        if (pathLen == 0) return root;
        return *path[pathLen-1];
    };

    /// Increments an iterator
    OctreeIterator& operator++ () 
    {
        assert (!null());
        debug ("PathLen="<< pathLen);
        if (pathLen == 0) {
            if (root->isLeaf()) {
                // Nowhere to go
                pathLen = -1;
                root = 0;
                debug ("Leaf root");
            }
            else {
                // Go down
                assert (path.size() == 0);
                path.push_back (((InternalNode*) root)->son);
                pathLen++;
                debug ("Down from root");
            }
        } 
        else {
            if ((*path[pathLen-1])->isLeaf ()) {
                /// Get sibling node if it exists
                debug ("leaf");
                do {
                    int i = sonIndex ();
                    debug ("sonindex=" << i);
                    if (i < 7) {
                        /// Node is not the last son - get sibling node
                        debug ("sibling");
                        path [pathLen-1]++;
                        break;
                    }
                    else {
                        /// Node is the last son - go up
                        debug ("up");
                        //assert (path.size () == pathLen);
                        pathLen--;
                        path.pop_back();
                        if (pathLen < 1) {
                            // Nowhere to go 
                            root = 0;
                            pathLen = -1;
                            break;
                        }
                    }
                } while (true);
            } 
            else 
            {
                /// Go down
                debug ("down");
                InternalNode * iNodePtr = (InternalNode*) *(path[pathLen-1]);
                path.push_back (iNodePtr->son);
                pathLen++;
                assert ((unsigned int)pathLen == path.size());
            }
        }        
    }
    
};

/** Base class for an octree data structure.
 *	@author <A HREF="mailto:esperanc@lcg.ufrj.br">Claudio Esperanca</a> and
 *	<A HREF="mailto:roma@lcg.ufrj.br">Paulo Roma Cavalcanti</a>
 *	@version $Revision: 1.19 $ $Date: 2004/04/29 11:10:17 $
 *	
 * This is the octree data structure most users will actually use.
 * Nodes ares split based on a given refinement criterion.
 * Default criterion is based on occupancy only.
 *
 * @param K Which CGAL Kernel to use
 * @param ItemPtr The octree will store pointers of this type
 * @param Refine given criterion.
 *
 */
template <class K, class ItemPtr, class Refine = OverflowRefine<K,ItemPtr> >
class Octree {

public:
    typedef typename CGAL::Point_3<K> Point3;   ///< A Point in 3D
    typedef Box_3<K> Box3;             ///< Octant extent
    typedef list<ItemPtr> ItemPtrList; ///< What is actually stored in a leaf
    typedef set<ItemPtr> ItemPtrSet;   ///< Return type of overlap
    typedef OctreeIterator<K,ItemPtr,Refine> Iterator; ///< Octree pre-order iterator
    
protected:
    ///
    /// World covered by this octree
    ///
    Box3 world;

    ///
    /// Main OctreeNode pointer
    ///
    OctreeNode<K, ItemPtr, Refine> * root;

public :
    /// Main Constructor
    /// @param theWorld extent of the world covered by the octree
    Octree (const Box3& theWorld) : world (theWorld), root (0) {
       root = new OctreeLeafNode<K, ItemPtr, Refine>;
    }

    /// destructor. 
    virtual ~Octree() {}

    /// inserts a pointer to an object in this octree
    /// @param p pointer to object
    virtual void insert (const ItemPtr p) {
         root->insert (world, 0, p, root);
    }

    /// Returns the number of pointers to items inserted into this octree
    virtual int itemPtrCount () const {
      return root->itemPtrCount();
    }

    const OctreeNode<K, ItemPtr, Refine>* searchLeaf (const Point3& p) const
    {
    	//const OctreeNode<K, ItemPtr, Refine> * node = root->searchLeaf(world, p);
    	return root->searchLeaf(world, p);
    }

    /// Returns all items that overlap a given box
    /// @param query query box
    ItemPtrSet overlap (const Box3 query) const {
       return root->overlap (world, query);
    }


    /// Returns all items that overlap a given sphere
    /// @param query query sphere
    ItemPtrSet overlap (const Sphere3 query) const {
       return root->overlap (world, query);
    }

	/// Returns all functions that overlap a given sphere
    /// @param query query sphere
    ItemPtrSet overlapfunc (const Sphere3 query) const {
       return root->overlapfunc (world, query);
    }

    /// Returns a pre-order iterator to the octree
    Iterator begin () {
        return Iterator (root);
    }

    /// Returns an iterator to past the end of the octree
    Iterator end () {
        return Iterator ();
    }
    
    /// Returns the box geometry of an octree node pointed to by an iterator
    Box3 box (const Iterator& i) const {
        double xsize = world.xmax() - world.xmin();
        double ysize = world.ymax() - world.ymin();
        double zsize = world.zmax() - world.zmin();
        double x0, y0, z0;
        i.minCoords (x0, y0, z0);
        Point3 minCorner (world.xmin() + x0 * xsize,
                          world.ymin() + y0 * ysize,
                          world.zmin() + z0 * zsize);
        double sizeFraction = 1.0 / (1 << i.level());
        return Box3 (minCorner,
                     Point3 (minCorner.x() + xsize * sizeFraction,
                             minCorner.y() + ysize * sizeFraction,
                             minCorner.z() + zsize * sizeFraction));
    }

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octreedistance
    ///
    /// @param p Point in relation to which the distance will be computed
    /// @return euclidean distance
    ///
    double distance (const Point3& p) const
    {
        return root->distance (world, HUGE, p);
    }

    /// Returns the euclidean distance between p and the closest object stored
    /// in the octree
    ///
    /// @param p Point in relation to which the distance will be computed
    /// @param clsPt Closest point on object.
    /// @return euclidean distance
    ///
    double distance (const Point3& p, Point3& clsPt) const
    {
        return root->distance (world, HUGE, p, clsPt);
    }

};
#endif

