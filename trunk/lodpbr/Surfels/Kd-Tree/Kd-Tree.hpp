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

#include <vector>
#include <map>

#include "Math/BoundingBox3.hpp"
#include "Math/Point3.hpp"

#include "Kd-TreeNode.hpp"
#include "Kd-TreeRefine.hpp"

/**
 * Base class for a kd-tree data structure -- only 3D!
 *
 * @param Real type to use (float, double ... )
 * @param Item The kd-tree will store this type
 * @param Refine give criterion
 *
 **/
template <class Real,class SurfelPtr, class Refine = OverflowKdTreeRefine<Real,SurfelPtr> >
class KdTree  {

public:

  typedef typename 	Celer::Point3<Real> 												Point3;     ///< A Point in 3D
  typedef typename 	Celer::BoundingBox3<Real> 										Box3;

  /// List of what is actually stored in a leaf node (non-leaf nodes stores only one reference)

	typedef  std::vector<SurfelPtr>												SurfelPtrVector;
	typedef typename  SurfelPtrVector::iterator									SurfelPtrVectorIterator;

  /// kd-tree node
  typedef 			KdTreeNode<Real,SurfelPtr, Refine> 								    Node;

  /// Map definitions for k-nearest neighbors algorithm
  typedef 			std::multimap <Real, SurfelPtr, std::greater<Real> > 				KNearestMap;
  typedef typename 	std::multimap <Real, SurfelPtr, std::greater<Real> >::iterator 	    KNearestMapIterator;
  typedef 			std::pair<Real, SurfelPtr> 										    KNearestPair;

protected:



public:

  /// kd-tree root node
  KdTreeNode <Real,SurfelPtr, Refine> * root;

  KdTree() : root (0)
  {

  };

  /// Main Constructor
  KdTree (const Box3& theWorld)
  {
	if (root)
		delete root;
	root = 0;
    root = new KdTreeNode <Real,SurfelPtr, Refine> (theWorld);
  }

  bool Clear()
  {
	  if (root)
		  delete root;
	  root = 0;
	  return 1;
  }

  /// destructor
  virtual ~KdTree()
  {
//	  if (root)
//		  delete root;
//	  root = 0;
  }

  /// Inserts a pointer to an object in this kd-tree
  /// @param p pointer to object
  virtual void Insert (const SurfelPtr& p)
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
  virtual int Count (void) const
  {
    return root->Count();
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
  SurfelPtrVector KNearestNeighbors (const SurfelPtr& p, unsigned int k, int &comps) const
  {

	  KNearestMap kNearest;
	  
	  comps = root->KNearestNeighbors (p, kNearest, k);

	  SurfelPtrVector kCloose;
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

  
// =======================================================================================//

  SurfelPtrVector KNearestNeighborsClustering ( SurfelPtr& p, unsigned int k, int &comps)
  {

	  KNearestMap kNearest;
	  comps = root->KNearestNeighborsClustering (p, kNearest, k);

	  SurfelPtrVector kCloose;
	  KNearestMapIterator i;

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
