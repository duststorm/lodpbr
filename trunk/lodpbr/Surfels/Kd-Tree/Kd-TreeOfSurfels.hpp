/**
 * Base class for 3d-Tree
 * @author <A HREF="mailto:ricardo@lcg.ufrj.br">Ricardo Marroquim</a> and
 * <A HREF="mailto:fmc@lcg.ufrj.br">Felipe Carvalho</a>
 * @version $Revision: 1.20 $ $Date: 2008/09/24 16:01:00 $
 *
 * To make this kd-tree more generic must create a template function
 * to support insertion and search function.
 * As it is ItemPtr must implement a "cartesian" method that returns
 * it's x, y, and z coordinates .
 * Also, distance function assumes item is a point and uses
 * SquaredDistance function.
 *
 **/

#ifndef KDTREE_HPP_
#define KDTREE_HPP_

#include "Kd-TreeNodeOfSurfels.hpp"
#include "Kd-TreeOfSurfelsRefine.hpp"

/**
 * Base class for a kd-tree data structure -- only 3D!
 *
 * @param Real type to use (float, double ... )
 * @param Item The kd-tree will store this type
 * @param Refine give criterion
 *
 **/
template <class Surfel, class Refine = OverflowKdTreeRefine<Surfel> >
class KdTree {

public:
  /// kd-tree node

  typedef 			KdTreeNode<Surfel, Refine> 	 Node;

protected:


public:

  /// kd-tree root node
  Node* root;

  KdTree() : root (0)
  {

  };

  /// Main Constructor
  KdTree (const typename Surfel::Box3& theWorld)
  {
    root = new KdTreeNode <Surfel, Refine> (theWorld);
  }

  /// destructor
  virtual ~KdTree(bool delElemets)
  {
	 root->~Node(delElemets);
  }

  /// Inserts a pointer to an object in this kd-tree
  /// @param p pointer to object
  virtual void Insert (const typename Surfel::Pointer& p)
  {
	  // Check if point is inside kd-tree world before inserting
	  if ( (p->Center().x >= root->Box().xMin()) && (p->Center().x <= root->Box().xMax()) &&
		   (p->Center().y >= root->Box().yMin()) && (p->Center().y <= root->Box().yMax()) &&
		   (p->Center().z >= root->Box().zMin()) && (p->Center().z <= root->Box().zMax()) )

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
  const Node* Search (const typename Surfel::Point3& p) const
  {
    return root->Search (p);
  }

  /// Returns the nearesNeighbor to a given point
  /// @param p Given point.
  /// @return Pointer to the nearest neighbor object.
  typename Surfel::VectorOfPointerSurfel KNearestNeighbors (
		  const typename Surfel::Pointer& p,
		  unsigned int 					  k,
		  int 							  &comps) const
  {

	  typename Surfel::KNearestMap kNearest;
	  
	  comps = root->KNearestNeighbors (p, kNearest, k);

	  typename Surfel::VectorOfPointerSurfel kCloose;
	  typename Surfel::KNearestMapIterator i;

	  
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

  
// =======================================================================================//

  typename Surfel::VectorOfPointerSurfel KNearestNeighborsClustering (
		  typename Surfel::Pointer& p,
		  unsigned int 				k,
		  int 						&comps)
  {

	  typename Surfel::KNearestMap kNearest;
	  comps = root->KNearestNeighborsClustering (p, kNearest, k);

	  typename Surfel::VectorOfPointerSurfel kCloose;
	  typename Surfel::KNearestMapIterator i;

	  for (i = kNearest.begin (); i != kNearest.end(); ++i)
	  {
		  kCloose.push_back (i->second);
	  }

	  return kCloose;
  }
  
  void ResetMarkedClustering()
  {
	  if (root != 0)
	  {
		  root->ResetMarkedClustering();
	  }
  }

};

#endif /*KDTREE_HPP_*/
