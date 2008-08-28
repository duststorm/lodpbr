#ifndef KDTREEREFINE_HPP_
#define KDTREEREFINE_HPP_

#include <vector>
///
/// Refinement criteria for kd-tree
///
template <class Real,class ItemPtr>
struct KdTreeRefine {
  typedef typename LAL::Point3<Real> 		Point3;     ///< A Point in 3D
  typedef typename LAL::BoundingBox3<Real> 	Box3; 
  /// Decides whether or not to split a leaf node
  static bool split (const Box3& world, const std::vector<ItemPtr>& items) {
    return false;
  }
};

///
/// A simple refinement criteria for leaf nodes based on occupancy.
/// A node is refined whenever it hold more than "Max" items
///
template <class Real,class ItemPtr, int Max=3>
struct OverflowRefineKD : public KdTreeRefine <Real,ItemPtr> {
	
  typedef typename LAL::Point3<Real> 		Point3;     ///< A Point in 3D
  typedef typename LAL::BoundingBox3<Real> 	Box3; 
  /// Split a leaf node iff the list contains more than Max items
  static bool split (const Box3& world, const std::vector<ItemPtr>& items) {
    return items.size() > Max;
  }
};

#endif /*KDTREEREFINE_HPP_*/
