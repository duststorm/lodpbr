#ifndef __OCTREE_INTERSECT__
#define __OCTREE_INTERSECT__

#include "slal/BoundingBox3.hpp"
#include "slal/Point3.hpp"
/// defines methods dependent on the geometry of the itens into the octree.
namespace lcgOctree {

///
/// Intersection test between a box and a point in 3D
///
template <class K>
bool checkIntersection (const SLAL::BoundingBox3<K>& box, SLAL::Point3<K>* p) {
    return p->x() >= box.xmin() && p->x() < box.xmax() &&
           p->y() >= box.ymin() && p->y() < box.ymax() &&
           p->z() >= box.zmin() && p->z() < box.zmax();
}

/// Returns the euclidean distance between a point and a point in 3D space
/// @param pt given point.
/// @param p given point.
/// @param clsPt closest point on object.
/// @return distance between p and the polygon.
template <class K>
  double distance2Item (const SLAL::Point3<K>* pt, const SLAL::Point3<K>& p, SLAL::Point3<K>& clsp)
  {
    clsp = *pt;
    SLAL::Point3<K> q = *pt;
    double a, b;
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
