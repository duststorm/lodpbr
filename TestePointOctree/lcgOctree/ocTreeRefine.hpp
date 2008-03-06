#ifndef OCTREEREFINE_HPP_
#define OCTREEREFINE_HPP_

//[STL container includes]
#include <list>

//[Project includes]
#include "ocTreeBox.hpp"
#include "ocTreeIntersection.hpp"

///
/// Refinement criteria for octrees
///
template <class Real, class ItemPtr>
struct OctreeRefine {
    ///
    /// Decides whether or not to split a leaf node
    /// @param world space of the node octant
    /// @param level node level
    /// @param items list of items inside the leaf node
    static bool split (const Box_3<Real>& world, int level, const std::list<ItemPtr>& items) {
        return false;
    }
};

/// 
/// A Simple Refinement Criteria for leaf nodes based on occupancy.
/// A node is refined whenever it holds more than "Max" items, and 
/// the subdivision level has not reached "LevelMax".
///
template <class Real, class ItemPtr, int Max = 1, int LevelMax = 5>
struct OverflowRefine : public OctreeRefine <Real, ItemPtr> {
    ///
    /// Split a leaf node iff the list contains more than Max items
    /// @param world space of the node octant
    /// @param level node level
    /// @param items list of items inside the leaf node
    static bool split (const Box_3<Real>& world, int level, const std::list<ItemPtr>& items) {
        return items.size() > Max && level < LevelMax;
    }
};


#endif /*OCTREEREFINE_HPP_*/
