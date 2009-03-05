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
/// @param Item item type to be stored
/// @param Refine refinement criteria
///
template < class Real,class ItemPtr, class Refine = OverflowKdTreeRefine<Real,ItemPtr> >
class KdTreeNode {

  typedef typename 	LAL::Point3<Real> 									Point3;     ///< A Point in 3D
  typedef typename 	LAL::BoundingBox3<Real> 							Box3;
  /// List of what is actually stored in a leaf node (non-leaf nodes stores only one reference)
  typedef 			std::vector<ItemPtr> 									ItemPtrList;
  typedef const 	KdTreeNode* 											NodePtr;

  typedef 			std::multimap < Real, ItemPtr, std::greater<Real> >		KNearestMap;
  typedef 		  	std::pair< Real, ItemPtr > 								KNearestPair;

private:

  /// Split dimension, 0 for X, 1 for Y and 2 for Z (internal nodes only)
  int mSplitDimension;

  /// Coordinate where the node space was split in two (internal nodes only)
  double mSplitCoordnate;

  /// Pointers to left and right subtrees (if both are null it is a leaf node)
  KdTreeNode * son[2];

  /// Pointer to parent node
  KdTreeNode * mFather;

  /// Node's coordinates
  Box3 mWorld;

public:

  /// List of pointers to points contained in node (if it is leaf) or point that
  /// splits this node in two
  ItemPtrList 	   mListPtr;
  /// constructor
  KdTreeNode (const Box3& w) : mWorld(w)
  {

	son[1] 	= 0;
	son[0] 	= 0;
	mFather 	= 0;

    mSplitDimension = 0;
    mSplitCoordnate = 0;

  }

  /// constructor
  KdTreeNode (KdTreeNode* f, const Box3& w) : mFather(f), mWorld(w)
  {
	son[1] 		= 0;
	son[0] 		= 0;
    mSplitDimension = 0;
    mSplitCoordnate = 0;
  }

  /// destructor
  virtual ~KdTreeNode ()
  {

    if (son[0] != 0)
    {
    	delete son[0];
    }
    if (son[1] != 0)
    {
    	delete son[1];
    }

  }

  /// Returns a pointer to the kd-tree node which contains point p
  /// @param p point which should be inside a descendant
  const KdTreeNode* SearchLeaf (const ItemPtr& p) const
  {
	  if (mListPtr.size() == 1)
	  { // internal node, contains only one object
		  if (p->Center() == mListPtr[0]->Center()) // found match
		  {
			  return this;
		  }
		  else
		  {
			  if (p->Center()[mSplitDimension] > mSplitCoordnate)
			  {
				  return son[1]->SearchLeaf (p);
			  }else
			  {
				  return son[0]->SearchLeaf (p);
			  }
		  }

	  }else if (mListPtr.size() > 1)
	  { // leaf node, search entire list for a match
		  for (int i = 0; i < mListPtr.size(); ++i)
		  {
			  if (mListPtr[i]->Center() == p.Center())
			  {
				  return this;
			  }
		  }

		  return NULL;
	  }
  }

  /// Returns the left son of this node
  /// @return left son
  const KdTreeNode* Left(void) const
  {
    return son[0];
  }

  /// Returns the right son of this node
  /// @return right son
  const KdTreeNode* Right(void) const
  {
    return son[1];
  }

  /// Returns the parent of this node
  /// @return parent node
  const KdTreeNode* Parent(void) const
  {
    return mFather;
  }

  /// Searches for the leaf node containing p
  /// @param p Given point
  /// @return Pointer to node containing p
  const KdTreeNode* Search (ItemPtr p)
  {
	  if (IsLeaf())
	  {
		  return this;
	  }
	  if (p->Center()[mSplitDimension] < mSplitCoordnate)
	  {
		  return son[0]->search (p);
	  }
	  else
	  {
		  return son[1]->search (p);
	  }
  }

  /// Computes the squared distance from a given point to the nodes box
  /// @param p Given point
  /// @return Squared distance
  Real EuclideanDistanceToBox (const Point3& p) const
  {

	  Point3 closestPoint = p; //closest point on box to p

	  if (p.x <= mWorld.xMin())
	  {
		  closestPoint = Point3(mWorld.xMin(), closestPoint.y, closestPoint.z);
	  }
	  else if (p.x >= mWorld.xMax())
	  {
		  closestPoint = Point3(mWorld.xMax(), closestPoint.y, closestPoint.z);
	  }

	  if (p.y <= mWorld.yMin())
	  {
		  closestPoint = Point3(closestPoint.x, mWorld.yMin(), closestPoint.z);
	  }
	  else if (p.y >= mWorld.yMax())
	  {
		  closestPoint = Point3(closestPoint.x, mWorld.yMax(), closestPoint.z);
	  }

	  if (p.z <= mWorld.zMin())
	  {
		  closestPoint = Point3(closestPoint.x, closestPoint.y, mWorld.zMin());
	  }
	  else if (p.z >= mWorld.zMax())
	  {
		  closestPoint = Point3(closestPoint.x, closestPoint.y, mWorld.zMax());
	  }

    return p.EuclideanDistance(closestPoint);
  }

  // -------------------------------------------------------------------------------------//


  /// Inserts a point in the set of k-nearest points
  /// If the set exceeds the k-limit, removes the point farthest away (first of set)
  /// @param item Neighbor to be inserted
  /// @param dist distance from p to search point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  /// @return The distance to the farthest point in the map
  Real InsertNeighbor (const ItemPtr& itemPtr, Real dist, KNearestMap& pKNearest, unsigned int k) const
  {
	  pKNearest.insert ( KNearestPair (dist, itemPtr) );
	  // if list has more than k nearest neighbors, remove first element (greater distance)
	  if (pKNearest.size() > k)
	  {
		  pKNearest.erase( pKNearest.begin() );
		  
	  }
	  return pKNearest.begin()->first;
  }

  /// Computes the k-nearest neighbors inside this node to the given point p
  /// @param p Given point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  /// @return Number of distance comparisons made
  int KNearestLocalNeighbors (const ItemPtr& p, KNearestMap& pKNearest, unsigned int k) const
  {
	  int comps = 0;
	  Real minDist;

	  if (pKNearest.empty())
	  {
		  minDist = HUGE; // empty set of nearest points
	  }
	  else
	  {
		  minDist = pKNearest.begin()->first; // greatest distance of all points in map
	  }

	  // compute distance to all points inside the node (in case of internal nodes there is only one)
	  for (unsigned int i = 0; i < mListPtr.size(); ++i)
	  {
		  ItemPtr q = mListPtr[i];

		  if (mListPtr[i]->Center() != p->Center())
		  { // Check if not trying to insert itself
			  Real dist = p->Center().EuclideanDistance (q->Center());
			  ++comps;
			  if (dist < minDist || pKNearest.size() < k)
			  {
				  minDist = InsertNeighbor (mListPtr[i], dist, pKNearest, k);
			  }
		  }
	  }
	  return comps;
  }

  /// Computes the k-nearest neighbors inside the kd-tree to a given point
  /// @param p Given point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  int KNearestNeighbors (const ItemPtr& p, KNearestMap& pKNearest, unsigned int k) const
  {
	  int comps = 0;
	  // Computes the distance to this node's itens
	  comps = KNearestLocalNeighbors (p, pKNearest, k);

	  if (!IsLeaf()) // Descend to child nodes
	  {
		  // Compute distance from p to son's box
		  Real dists[2] = {son[0]->EuclideanDistanceToBox (p->Center()), son[1]->EuclideanDistanceToBox (p->Center())};
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
		  Real best = pKNearest.begin()->first;

		  if (dists[order[0]] < best || pKNearest.size() < k)
		  {
			  comps += son[order[0]]->KNearestNeighbors (p, pKNearest, k);
		  }

		  best = pKNearest.begin()->first;

		  if (dists[order[1]] < best || pKNearest.size() < k)
		  {
			  comps += son[order[1]]->KNearestNeighbors (p, pKNearest, k);
		  }

	  }

	  return comps;
  }

  // -------------------------------------------------------------------------------------//


  /// Inserts a pointer to an object in this kd-tree node
  /// @param level kd-tree level of this node
  /// @param p pointer to object
  /// @param fatherPtr reference to the pointer inside the father which point to this node
  void Insert (int level, const ItemPtr& p)
  {

	  if (son[0] == 0 && son[1] == 0)
	  { // leaf node
		  
		  mListPtr.push_back(p);

		  // Check if overflow criteria is met
		  if (Refine::Split (mWorld, mListPtr))
		  {

			  /// Check largest box dimension for subdivision
			  mSplitDimension = (mWorld.Max().x - mWorld.Min().x > mWorld.Max().y - mWorld.Min().y) ? 0 : 1;
			  mSplitDimension = (mWorld.Max()[mSplitDimension] - mWorld.Min()[mSplitDimension] > mWorld.Max().z - mWorld.Min().z) ? mSplitDimension : 2;

			  /// Search for point closest to the center of mSplitDimension
			  Real center = 0.5 * (mWorld.Max()[mSplitDimension] + mWorld.Min()[mSplitDimension]);
			  Real minDist = HUGE;

			  ItemPtr middleItem;
			  for (unsigned int i = 0; i < mListPtr.size(); ++i)
			  {
				  Real dist = fabs (center - mListPtr[i]->Center()[mSplitDimension]);

				  if (dist < minDist)
				  {
					  minDist = dist;
					  middleItem = mListPtr[i];
				  }
			  }


			  // Defines the position of the space partition
			  mSplitCoordnate = middleItem->Center()[mSplitDimension];

			  // Create two son nodes
			  KdTreeNode * newLeftNode  = new KdTreeNode(this, LeftBox());
			  KdTreeNode * newRightNode = new KdTreeNode(this, RightBox());

			  son[0] = newLeftNode;
			  son[1] = newRightNode;

			  // Insert items from list into child nodes (except middle item)
			  for (unsigned int i = 0; i < mListPtr.size(); ++i)
			  {

				  if (mListPtr[i]->Center()[mSplitDimension] <= mSplitCoordnate)
				  {
					  if (!(mListPtr[i]->Center() == middleItem->Center()))
					  {
						  son[0]->Insert(level + 1, mListPtr[i]);
					  }

				  }
				  // Here was a error =\ , with small number of itens in the node like 2 or 3
				  else //if (mListPtr[i][mSplitDimension] > mSplitCoordnate)
				  {

					  son[1]->Insert(level + 1, mListPtr[i]);
				  }
			  }

			  // Insert split object into this node's empty list
			  mListPtr.clear();
			  mListPtr.push_back(middleItem);

		  }
	  }
	  else
	  { // internal node, continue descending
		  if ( p->Center()[mSplitDimension] < mSplitCoordnate )
		  {
			  son[0]->Insert(level + 1, p);
		  }
		  else
		  {
			  son[1]->Insert(level + 1, p);
		  }
	  }
  }

  /// Returns the number of pointers to items inserted into this node
  /// @return Size of item list
  int ItemPtrCount () const {
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
	return mListPtr.size();
  }

  /// Returns the ith element of the item list
  /// @param id The element position
  /// @return ith element of item list
  const ItemPtr Element (int id) const
  {
    return mListPtr[id];
  }

  /// Returns one of two sons of this node
  /// @param id Son identification (0 = left/bottom; 1 = right/top)
  /// @return Child node
  KdTreeNode * Son(int id)
  {
	  if (id == 0 || id == 1)
	  {
		  return son[id];
	  }
	  return NULL;
  }

  /// Returns the position where the split occurred
  /// @return Split coordinate
  Real SplitCoordinate(void)
  {
    return mSplitCoordnate;
  }

  /// Returns the axis where the split occurred
  /// @return Split dimension (axis)
  int SplitDimension(void)
  {
    return mSplitDimension;
  }

  /// Returns if this is leaf node or not
  /// @return 1 if leaf node, 0 otherwise
  bool IsLeaf () const
  {
	  return son[0] == 0 && son[1] == 0;
  }

  /// Returns the mWorld coordinates
  /// @return World coodinates of this node
  const Box3 Box(void) const
  {
	  return mWorld;
  }

 // ====================================== Only for Clustering ============================================//


  /// Computes the k-nearest neighbors inside this node to the given point p
  /// @param p Given point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  /// @return Number of distance comparisons made
  int KNearestLocalNeighborsClustering ( ItemPtr& p, KNearestMap& pKNearest, unsigned int k) 
  {
	  int comps = 0;
	  Real minDist;

	  if (pKNearest.empty())
	  {
		  minDist = HUGE; // empty set of nearest points
	  }
	  else
	  {
		  minDist = pKNearest.begin()->first; // greatest distance of all points in map
	  }

	  // compute distance to all points inside the node (in case of internal nodes there is only one)
	  for (unsigned int i = 0; i < mListPtr.size(); ++i)
	  {
		  ItemPtr q = mListPtr[i];
		 
		  if (mListPtr[i]->Marked() == 0) // Test if the item has been add 
		  {
			  if (mListPtr[i]->Center() != p->Center())
			  { // Check if not trying to insert itself
				  Real dist = p->Center().EuclideanDistance (q->Center());
				  ++comps;
				  if (dist < minDist || pKNearest.size() < k)
				  {		
					  
//					   std::cout << (p.Normal() * q.Normal()) << " - "<< p.Normal() << "- " << q.Normal() << std::endl;
					  //if ( (p.Normal() * q.Normal()) > 0.85 )
					  {
						  pKNearest.insert ( KNearestPair (dist, mListPtr[i]) );
						  mListPtr[i]->SetMarked(1);

						  if ( pKNearest.size() > k)
						  {
							  pKNearest.begin()->second->SetMarked(0);
							  pKNearest.erase( pKNearest.begin() );
						  }
						  minDist = pKNearest.begin()->first;
					  }
  
				  }
			  }
		  }
	  }
	  return comps;
  }

  /// Computes the k-nearest neighbors inside the kd-tree to a given point
  /// @param p Given point
  /// @param k_nearest Ordered set of nearest neighbors
  /// @param k Number of nearest neighbors to find
  int KNearestNeighborsClustering ( ItemPtr& p, KNearestMap& pKNearest, unsigned int k) 
  {
	  int comps = 0;
	  // Computes the distance to this node's itens
	  comps = KNearestLocalNeighborsClustering (p, pKNearest, k);

	  if (!IsLeaf()) // Descend to child nodes
	  {
		  // Compute distance from p to son's box
		  Real dists[2] = {son[0]->EuclideanDistanceToBox (p->Center()), son[1]->EuclideanDistanceToBox (p->Center())};
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
		  Real best = pKNearest.begin()->first;

		  if (dists[order[0]] < best || pKNearest.size() < k)
		  {
			  comps += son[order[0]]->KNearestNeighborsClustering (p, pKNearest, k);
		  }

		  best = pKNearest.begin()->first;

		  if (dists[order[1]] < best || pKNearest.size() < k)
		  {
			  comps += son[order[1]]->KNearestNeighborsClustering (p, pKNearest, k);
		  }

	  }

	  return comps;
  }
  
  /// Reset the element to not marked
  /// This is useful for clustering algorithm
  /// to avoid build the whole clustering again 
  void ResetMarkedClustering()
  {
	  
	  	  for (unsigned int i = 0; i < mListPtr.size(); ++i)
	  	  {
	  		  mListPtr[i]->SetMarked(0);
	  	  }
		  
		  if (son[0] != 0)
		  {
			  son[0]->ResetMarkedClustering();
		  }
		  if (son[1] != 0)
		  {
			  son[1]->ResetMarkedClustering();
		  }
	 
  }	

private :

  /// Computes the left son world coordinates
  /// @return Left son world coordinates
	Box3 LeftBox (void) const
	{
		Box3 leftWorld;
		Point3 pointMax;

		if (mSplitDimension == 0) // recompute x coordinate range
		{
			pointMax = Point3 (mSplitCoordnate, mWorld.yMax(), mWorld.zMax());
		}
		else if (mSplitDimension == 1)
		{
			pointMax = Point3 (mWorld.xMax(), mSplitCoordnate, mWorld.zMax());
		}
		else
		{
			pointMax = Point3 (mWorld.xMax(), mWorld.yMax(), mSplitCoordnate);
		}

		leftWorld = Box3 (mWorld.Min(), pointMax);

		return leftWorld;
	}

  /// Computes the right son world coordinates
  /// @return Right son world coordinates
	Box3 RightBox (void) const
	{
		Box3 rightWorld;
		Point3 pointMin;

		if (mSplitDimension == 0) // recompute x coordinate range
		{
			pointMin = Point3 (mSplitCoordnate, mWorld.yMin(), mWorld.zMin());
		}
		else if (mSplitDimension == 1)
		{
			pointMin = Point3 (mWorld.xMin(), mSplitCoordnate, mWorld.zMin());
		}
		else
		{
			pointMin = Point3 (mWorld.xMin(), mWorld.yMin(), mSplitCoordnate);
		}

		rightWorld = Box3 (pointMin, mWorld.Max());

		return rightWorld;
	}
	

};

#endif /*KDTREENODE_HPP_*/
