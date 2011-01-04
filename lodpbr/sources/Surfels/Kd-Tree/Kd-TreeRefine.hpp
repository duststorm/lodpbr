#ifndef KDTREEREFINE_HPP_
#define KDTREEREFINE_HPP_

#include <vector>
#include "Math/BoundingBox3.hpp"
///
/// Refinement criteria for kd-tree
///
template <class Real,class SurfelPtr>
struct KdTreeRefine
{

  typedef Celer::BoundingBox3<Real> 			Box3;
  typedef  			std::vector<SurfelPtr>		SurfelPtrVector;

  /// Decides whether or not to split a leaf node
  static bool Split (const Box3& world, const SurfelPtrVector& items)
  {
    return false;
  }

};
///
/// A simple refinement criteria for leaf nodes based on occupancy.
/// A node is refined whenever it hold more than "Max" items
///
template <class Real,class SurfelPtr, int Max=3>
struct OverflowKdTreeRefine : public KdTreeRefine <Real,SurfelPtr>
{

  typedef Celer::BoundingBox3<Real> 			Box3;
  typedef  			std::vector<SurfelPtr>		SurfelPtrVector;

  /// Split a leaf node if the list contains more than Max items
  static bool Split (const Box3& world, const SurfelPtrVector& items)
  {
    return items.size() > Max;
  }

};

#endif /*KDTREEREFINE_HPP_*/
