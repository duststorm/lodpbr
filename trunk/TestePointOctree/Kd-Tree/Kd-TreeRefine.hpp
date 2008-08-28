#ifndef KDTREEREFINE_HPP_
#define KDTREEREFINE_HPP_

///
/// Refinement criteria for kd-tree
///
template <class ItemPtr>
struct KdTreeRefine {

  /// Decides whether or not to split a leaf node
  static bool split (const Box& world, const vector<ItemPtr>& items) {
    return false;
  }
};

///
/// A simple refinement criteria for leaf nodes based on occupancy.
/// A node is refined whenever it hold more than "Max" items
///
template <class ItemPtr, int Max=3>
struct OverflowRefine : public KdTreeRefine <ItemPtr> {

  /// Split a leaf node iff the list contains more than Max items
  static bool split (const Box& world, const vector<ItemPtr>& items) {
    return items.size() > Max;
  }
};

#endif /*KDTREEREFINE_HPP_*/
