#ifndef KDTREENODE_HPP_
#define KDTREENODE_HPP_

#include <map>
#include <vector>

#include "math/BoundingBox3.hpp"
#include "math/Point3.hpp"

#include "Kd-TreeRefine.hpp"
///
/// A KdTree of Pointers to Objects
///
/// @param K Kernel
/// @param ItemPtr item pointer type to be stored
/// @param Refine refinement criteria
///
template < class Real,class ItemPtr, class Refine = OverflowRefineKD<Real,ItemPtr> >
class KdTreeNode {

  typedef typename LAL::Point3<Real> 		Point3;     ///< A Point in 3D
  typedef typename LAL::BoundingBox3<Real> 	Box3;
  /// List of what is actually stored in a leaf node (non-leaf nodes stores only one reference)
  typedef std::vector<ItemPtr> ItemPtrList;
  typedef const KdTreeNode * NodePtr;

  typedef std::multimap < Real, ItemPtr, std::greater<Real> > K_NearestMap;
  typedef std::pair< Real, ItemPtr> K_NearestPair;

private:

  /// Split dimension, 0 for X, 1 for Y and 2 for Z (internal nodes only)
  int split_dim;

  /// Coordinate where the node space was split in two (internal nodes only)
  double split_coord;

  /// Pointers to left and right subtrees (if both are null it is a leaf node)
  KdTreeNode * son[2];

  /// Pointer to parent node
  KdTreeNode * father;

  /// List of pointers to points contained in node (if it is leaf) or point that
  /// splits this node in two
  ItemPtrList PtrList;

  /// Node's coordinates
  Box3 world;

public:

  /// constructor
  KdTreeNode (const Box3& w) : world(w) {
    son [0] = son [1] = 0;
    split_dim = 0;
    split_coord = 0;
    father = 0;
  }

  /// constructor
  KdTreeNode (KdTreeNode* f, const Box3& w) : father(f), world(w) {
    son [0] = son [1] = 0;
    split_dim = 0;
    split_coord = 0;
  }

  /// destructor
  ~KdTreeNode () {
    for (int i = 0; i < 2; ++i) {
      if (son [i] != 0) delete son[i];
    }
  }

  /// Returns a pointer to the kd-tree node which contains point p
  /// @param p point which should be inside a descendant
  const KdTreeNode* searchLeaf (const Point3& p) const {
    if (PtrList.size() == 1) { // internal node, contains only one object
      if (p == PtrList[0]) // found match
	return this;
      else {
	if (p[split_dim] > split_coord)
	  return son[1]->searchLeaf (p);
	else
	  return son[0]->searchLeaf (p);
      }
    }
    else if (PtrList.size() > 1) { // leaf node, search entire list for a match
      for (int i = 0; i < PtrList.size(); ++i) {
	if (PtrList[i] == p)
	  return this;
      }
      return NULL;
    }
  }

  /// Returns the left son of this node
  /// @return left son
  const KdTreeNode* left(void) const {
    return son[0];
  }

  /// Returns the right son of this node
  /// @return right son
  const KdTreeNode* right(void) const {
    return son[1];
  }

  /// Returns the parent of this node
  /// @return parent node
  const KdTreeNode* parent(void) const {
    return father;
  }

  /// Searches for the leaf node containing p
  /// @param p Given point
  /// @return Pointer to node containing p
  const KdTreeNode* search (Point3 p) {
    if (isLeaf())
      return this;

    if (p[split_dim] < split_coord)
      return son[0]->search (p);
    else
      return son[1]->search (p);
  }

  /// Computes the squared distance from a given point to the nodes box
  /// @param p Given point
  /// @return Squared distance
  double sqrtDistanceToBox (const Point3& p) const {

    Point3 cls = p; //closest point on box to p

    if (p.x <= world.xMin())
      cls = Point3(world.xMin(), cls.y, cls.z);
    else if (p.x >= world.xMax())
      cls = Point3(world.xMax(), cls.y, cls.z);

    if (p.y <= world.yMin())
      cls = Point3(cls.x, world.yMin(), cls.z);
    else if (p.y >= world.yMax())
      cls = Point3(cls.x, world.yMax(), cls.z);

    if (p.z <= world.zMin())
      cls = Point3(cls.x, cls.y, world.zMin());
    else if (p.z >= world.zMax())
      cls = Point3(cls.x, cls.y, world.zMax());

    return p.SquaredDistance(cls);
  }

  /// Inserts a point in the set of k-nearest points
  /// If the set exceeds the k-limit, removes the point farthest away (first of set)
  /// @param item Neighbor to be inserted
  /// @param dist distance from p to search point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  /// @return The distance to the farthest point in the map
  double insertNeighbor (ItemPtr item, double dist, K_NearestMap& k_nearest, unsigned int k) const {
    k_nearest.insert ( K_NearestPair (dist, item) );
    // if list has more than k nearest neighbors, remove first element (greater distance)
    if (k_nearest.size() > k)
      k_nearest.erase( k_nearest.begin() );
    return k_nearest.begin()->first;
  }

  /// Computes the k-nearest neighbors inside this node to the given point p
  /// @param p Given point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  /// @return Number of distance comparisons made
  int kNearestLocalNeighbors (const Point3& p, K_NearestMap& k_nearest, unsigned int k) const {
    int comps = 0;
    double minDist;
    if (k_nearest.empty())
      minDist = HUGE; // empty set of nearest points
    else
      minDist = k_nearest.begin()->first; // greatest distance of all points in map

    // compute distance to all points inside the node (in case of internal nodes there is only one)
    for (unsigned int i = 0; i < PtrList.size(); ++i) {
      Point3 q = *PtrList[i];
      if (*PtrList[i] != p) { // Check if not trying to insert itself
	double dist = p.SquaredDistance (q);
	++comps;
	if (dist < minDist || k_nearest.size() < k)
	  minDist = insertNeighbor (PtrList[i], dist, k_nearest, k);
      }
    }
    return comps;
  }

  /// Computes the k-nearest neighbors inside the kd-tree to a given point
  /// @param p Given point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  int kNearestNeighbors (const Point3& p, K_NearestMap& k_nearest, unsigned int k) const {
    int comps = 0;
    // Computes the distance to this node's itens
    comps = kNearestLocalNeighbors (p, k_nearest, k);

    if (!isLeaf()) // Descend to child nodes
      {
	// Compute distance from p to son's box
	Real dists[2] = {son[0]->sqrtDistanceToBox (p), son[1]->sqrtDistanceToBox (p)};
	comps += 2;
	int order[2] = {0, 1};

	// Arrange in order of distances (closest first)
	if (dists[1] < dists[0]) {
	  order[0] = 1;
	  order[1] = 0;
	}

	// Check distances to sons in ordered way, closest son first
	// Only checks if distance to son's box is less than distance to
	// farthes k-neighbor so far, or if hasn't found k-neighbots yet
	Real best = k_nearest.begin()->first;
	if (dists[order[0]] < best || k_nearest.size() < k)
	  comps += son[order[0]]->kNearestNeighbors (p, k_nearest, k);
	best = k_nearest.begin()->first;
	if (dists[order[1]] < best || k_nearest.size() < k)
	  comps += son[order[1]]->kNearestNeighbors (p, k_nearest, k);

      }

    return comps;
  }

  /// Inserts a pointer to an object in this kd-tree node
  /// @param level kd-tree level of this node
  /// @param p pointer to object
  /// @param fatherPtr reference to the pointer inside the father which point to this node
  void insert (int level, const ItemPtr p) {

	  if (son[0] == 0 && son[1] == 0) { // leaf node
		  PtrList.push_back(p);


		  // Check if overflow criteria is met
		  if (Refine::split (world, PtrList)) {

			  /// Check largest box dimension for subdivision
			  split_dim = (world.Max().x - world.Min().x > world.Max().y - world.Min().y) ? 0 : 1;
			  split_dim = (world.Max()[split_dim] - world.Min()[split_dim] > world.Max().z - world.Min().z) ? split_dim : 2;

			  /// Search for point closest to the center of split_dim
			  Real center = 0.5 * (world.Max()[split_dim] + world.Min()[split_dim]);
			  Real minDist = HUGE;

			  ItemPtr middleItem = NULL;
			  for (unsigned int i = 0; i < PtrList.size(); ++i) {
				  double dist = fabs (center - (*PtrList[i])[split_dim]);

				  if (dist < minDist) {
					  minDist = dist;
					  middleItem = PtrList[i];
				  }
			  }

			  // Defines the position of the space partition
			  split_coord = (*middleItem)[split_dim];

			  // Create two son nodes
			  KdTreeNode * newLeftNode = new KdTreeNode(this, leftBox());
			  KdTreeNode * newRightNode = new KdTreeNode(this, rightBox());
			  son[0] = newLeftNode;
			  son[1] = newRightNode;

			  // Insert items from list into child nodes (except middle item)
			  for (unsigned int i = 0; i < PtrList.size(); ++i) {
				  if ((*PtrList[i])[split_dim] < split_coord)
					  son[0]->insert(level + 1, PtrList[i]);
				  else if ((*PtrList[i])[split_dim] > split_coord)
					  son[1]->insert(level + 1, PtrList[i]);
			  }

			  // Insert split object into this node's empty list
			  PtrList.clear();
			  PtrList.push_back(middleItem);
		  }
	  }
	  else { // internal node, continue descending
		  if ((*p)[split_dim] < split_coord)
			  son[0]->insert(level + 1, p);
		  else
			  son[1]->insert(level + 1, p);
	  }
  }

  /// Returns the number of pointers to items inserted into this node
  /// @return Size of item list
  int itemPtrCount () const {
//	  int sum = 0;
//
//	  if (son[0] == 0 && son[1] == 0)
//		  return PtrList.size();
//	  else
//	  {
//		  sum += son[0]->itemPtrCount();
//		  sum += son[1]->itemPtrCount();
//	  }
//
//	  return  sum + PtrList.size();
	return PtrList.size();
  }

  /// Returns the ith element of the item list
  /// @param id The element position
  /// @return ith element of item list
  const ItemPtr element (int id) const {
    return PtrList[id];
  }

  /// Returns one of two sons of this node
  /// @param id Son identification (0 = left/bottom; 1 = right/top)
  /// @return Child node
  KdTreeNode * getSon(int id) {
    if (id == 0 || id == 1)
      return son[id];
    return NULL;
  }

  /// Returns the position where the split occurred
  /// @return Split coordinate
  double splitCoordinate(void) {
    return split_coord;
  }

  /// Returns the axis where the split occurred
  /// @return Split dimension (axis)
  int splitDim(void) {
    return split_dim;
  }

  /// Returns if this is leaf node or not
  /// @return 1 if leaf node, 0 otherwise
  bool isLeaf () const { return son[0] == 0 && son[1] == 0; }

  /// Returns the world coordinates
  /// @return World coodinates of this node
  const Box3 getBox(void) const { return world; }


private :

  /// Computes the left son world coordinates
  /// @return Left son world coordinates
  Box3 leftBox (void) const {
    Box3 leftWorld;
    Point3 p_max;
    if (split_dim == 0) // recompute x coordinate range
      p_max = Point3 (split_coord, world.yMax(), world.zMax());
    else if (split_dim == 1)
      p_max = Point3 (world.xMax(), split_coord, world.zMax());
    else
      p_max = Point3 (world.xMax(), world.yMax(), split_coord);

    leftWorld = Box3 (world.Min(), p_max);
    return leftWorld;
  }

  /// Computes the right son world coordinates
  /// @return Right son world coordinates
  Box3 rightBox (void) const {
    Box3 rightWorld;
    Point3 p_min;
    if (split_dim == 0) // recompute x coordinate range
      p_min = Point3 (split_coord, world.yMin(), world.zMin());
    else if (split_dim == 1)
      p_min = Point3 (world.xMin(), split_coord, world.zMin());
    else
      p_min = Point3 (world.xMin(), world.yMin(), split_coord);
    rightWorld = Box3 (p_min, world.Max());
    return rightWorld;
  }
};

#endif /*KDTREENODE_HPP_*/
