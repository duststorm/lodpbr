#ifndef KDTREEREFINE_HPP_
#define KDTREEREFINE_HPP_
///
/// Refinement criteria for kd-tree
///


template <class Surfel >
struct KdTreeRefine
{
  /// Decides whether or not to split a leaf node
  static bool Split (const typename Surfel::Box3& world,
					 const typename Surfel::VectorOfPointerSurfel& items)
  {
    return false;
  }

};
///
/// A simple refinement criteria for leaf nodes based on occupancy.
/// A node is refined whenever it hold more than "Max" items
///
template <class Surfel, int Max=3>
struct OverflowKdTreeRefine : public KdTreeRefine <Surfel>
{
    /// Split a leaf node if the list contains more than Max items
  static bool Split (const typename Surfel::Box3& world,
					 const typename Surfel::VectorOfPointerSurfel& items)
  {
    return items.size() > Max;
  }

};

#endif /*KDTREEREFINE_HPP_*/
