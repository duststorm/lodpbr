/**
 * Header file for 3d-Tree
 *
 * Author : Ricardo Marroquim
 * Date created : 08-01-2007
 *
 * To make this kd-tree more generic must create a template function
 * to support insertion and search function.
 * As it is ItemPtr must implement a "cartesian" method that returns
 * it's x, y, and z coordinates (CGAL-style).
 * Also, distance function assumes item is a pointe and uses CGAL
 * squared_distance function.
 *
 **/

#ifndef __KDTREE__
#define __KDTREE__

#include <vector>
#include <map>
#include "surfels.h"

using namespace std;


/**
 * Base class for a kd-tree data structure -- only 3D!
 *
 * @param K CGAL Kernel to use
 * @param ItemPtr The kd-tree will store pointers of this type
 * @param Refine give criterion
 *
 **/
template <class ItemPtr, class Refine = OverflowRefine<ItemPtr> >
class KdTree {

public:
  /// List of what is actually stored in a leaf node (non-leaf nodes stores only one reference)
  typedef vector<ItemPtr> ItemPtrList;

  /// kd-tree node
  typedef KdTreeNode<ItemPtr, Refine> Node;
  
  /// Map definitions for k-nearest neighbors algorithm
  typedef multimap < double, ItemPtr, std::greater<double> > K_Map;
  typedef multimap <double, Point*, std::greater<double> >::iterator K_MapIterator;
  typedef pair<double, ItemPtr> K_NearestPair;

protected:

  /// kd-tree root node
  KdTreeNode <ItemPtr, Refine> * root;

public:

  /// Main Constructor
  KdTree (const Box& theWorld) : root (0) {
    root = new KdTreeNode <ItemPtr, Refine> (theWorld);
  }

  /// destructor
  virtual ~KdTree() {}

  /// Inserts a pointer to an object in this kd-tree
  /// @param p pointer to object
  virtual void insert (const ItemPtr p) {
    // Check if point is inside kd-tree world before inserting
    if ( (p->x() >= root->getBox().xmin()) && (p->x() <= root->getBox().xmax()) &&
	 (p->y() >= root->getBox().ymin()) && (p->y() <= root->getBox().ymax()) &&
	 (p->z() >= root->getBox().zmin()) && (p->z() <= root->getBox().zmax()))
      root->insert (0, p);
  }

  /// Returns the number of pointer to items inserted into this kd-tree
  virtual int itemPtrCount (void) const { 
    return root->itemPtrCount();
  }

  /// Returns an iterator to the leaf node containing a given point
  /// @param p Given point
  /// @return Pointer to leaf node containing p
  const Node* search (const Point& p) const {
    return root->search (p);
  }

  /// Returns the nearesNeighbor to a given point
  /// @param p Given point.
  /// @return Pointer to the nearest neighbor object.
  ItemPtrList kNearestNeighbors (const Point& p, unsigned int k, int &comps) const {

    K_Map k_nearest;
    comps = root->kNearestNeighbors (p, k_nearest, k);

    ItemPtrList k_cls;
    K_MapIterator i;

    for (i = k_nearest.begin (); i != k_nearest.end(); ++i)
      k_cls.push_back (i->second);

    return k_cls;
  }
  
  /// Returns pointer to root node
  /// @return Pointer to root node
  Node* begin(void) {
    return root;
  }


};

#endif
