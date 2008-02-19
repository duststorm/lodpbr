#ifndef __OCTREE_INTERSECT__
#define __OCTREE_INTERSECT__

#include "slal/BoundingBox3.hpp"
#include "slal/Point3.hpp"
/// defines methods dependent on the geometry of the itens into the octree.
namespace lcgOctree {

///
/// Intersection test between a box and a point in 3D
///
template <class Real>
bool checkIntersection (const SLAL::BoundingBox3<Real>& box, SLAL::Point3<Real>* p) {
    return p->x() >= box.xmin() && p->x() < box.xmax() &&
           p->y() >= box.ymin() && p->y() < box.ymax() &&
           p->z() >= box.zmin() && p->z() < box.zmax();
}

/// Returns the euclidean distance between a point and a point in 3D space
/// @param pt given point.
/// @param p given point.
/// @param clsPt closest point on object.
/// @return distance between p and the polygon.
template <class Real>
  Real distance2Item (const SLAL::Point3<Real>* pt, const SLAL::Point3<Real>& p, SLAL::Point3<Real>& clsp)
  {
    clsp = *pt;
    SLAL::Point3<Real> q = *pt;
    Real a, b;
    a = p[0] - q[0];
    b = a * a;
    a = p[1] - q[1];
    b += a * a;
    a = p[2] - q[2];
    b += a * a;
    return sqrt( b );
}

}



#endif
