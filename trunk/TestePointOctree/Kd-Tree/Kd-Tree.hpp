/**
 * Base class for 3d-Tree
 * @author <A HREF="mailto:ricardo@lcg.ufrj.br">Ricardo Marroquim</a> and
 * <A HREF="mailto:fmc@lcg.ufrj.br">Felipe Carvalho</a>
 * @version $Revision: 1.20 $ $Date: 2008/09/24 16:01:00 $
 * 
 * To make this kd-tree more generic must create a template function
 * to support insertion and search function.
 * As it is ItemPtr must implement a "cartesian" method that returns
 * it's x, y, and z coordinates (CGAL-style).
 * Also, distance function assumes item is a pointe and uses CGAL
 * squared_distance function.
 *
 **/

#ifndef KDTREE_HPP_
#define KDTREE_HPP_

#include <vector>
#include <map>

#include "math/BoundingBox3.hpp"
#include "math/Point3.hpp"

#include "Kd-TreeNode.hpp"
#include "Kd-TreeRefine.hpp"

/**
 * Base class for a kd-tree data structure -- only 3D!
 *
 * @param K CGAL Kernel to use
 * @param ItemPtr The kd-tree will store pointers of this type
 * @param Refine give criterion
 *
 **/
template <class Real,class ItemPtr, class Refine = OverflowKdTreeRefine<Real,ItemPtr> >
class KdTree {

public:

  typedef typename 	LAL::Point3<Real> 												Point3;     ///< A Point in 3D
  typedef typename 	LAL::BoundingBox3<Real> 										Box3;

  /// List of what is actually stored in a leaf node (non-leaf nodes stores only one reference)
  typedef 			std::vector<ItemPtr> 											ItemPtrList;

  /// kd-tree node
  typedef 			KdTreeNode<Real,ItemPtr, Refine> 								Node;

  /// Map definitions for k-nearest neighbors algorithm
  typedef 			std::multimap <Real, ItemPtr, std::greater<Real> > 				KNearestMap;
  typedef typename 	std::multimap <Real, ItemPtr, std::greater<Real> >::iterator 	KNearestMapIterator;
  typedef 			std::pair<Real, ItemPtr> 										KNearestPair;

protected:



public:

  /// kd-tree root node
  KdTreeNode <Real,ItemPtr, Refine> * root;
  
  KdTree() : root (0)
  {

  };

  /// Main Constructor
  KdTree (const Box3& theWorld) : root (0) 
  {
    root = new KdTreeNode <Real,ItemPtr, Refine> (theWorld);
  }

  /// destructor
  virtual ~KdTree() {}

  /// Inserts a pointer to an object in this kd-tree
  /// @param p pointer to object
  virtual void Insert (const ItemPtr p) 
  {
	  // Check if point is inside kd-tree world before inserting
	  if ( (p->x >= root->Box().xMin()) && (p->x <= root->Box().xMax()) &&
		   (p->y >= root->Box().yMin()) && (p->y <= root->Box().yMax()) &&
		   (p->z >= root->Box().zMin()) && (p->z <= root->Box().zMax()) )

	  {
		  root->Insert (0, p);
	  }
  }

  /// Returns the number of pointer to items inserted into this kd-tree
  virtual int ItemPtrCount (void) const 
  {
    return root->ItemPtrCount();
  }

  /// Returns an iterator to the leaf node containing a given point
  /// @param p Given point
  /// @return Pointer to leaf node containing p
  const Node* Search (const Point3& p) const 
  {
    return root->Search (p);
  }

  /// Returns the nearesNeighbor to a given point
  /// @param p Given point.
  /// @return Pointer to the nearest neighbor object.
  ItemPtrList KNearestNeighbors (const Point3& p, unsigned int k, int &comps) const 
  {

	  KNearestMap kNearest;
	  comps = root->KNearestNeighbors (p, kNearest, k);

	  ItemPtrList kCloose;
	  KNearestMapIterator i;

	  for (i = kNearest.begin (); i != kNearest.end(); ++i)
	  {
		  kCloose.push_back (i->second);
	  }

	  return kCloose;
  }

  /// Returns pointer to root node
  /// @return Pointer to root node
  Node* Begin(void) 
  {
	  return root;
  }


};

#endif /*KDTREE_HPP_*/
