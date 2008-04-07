#ifndef __OCTREE_INTERSECT__
#define __OCTREE_INTERSECT__

#include "slal/BoundingBox3.hpp"
#include "slal/Point3.hpp"
#include "surfels/surfel.hpp"

/// defines methods dependent on the geometry of the itens into the octree.
namespace lcgOctree {

///
/// Intersection test between a box and a point in 3D
///
template <class Real>
bool checkIntersection (const CGL::BoundingBox3<Real>& box, CGL::Point3<Real>* p) {
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
Real distance2Item (const CGL::Point3<Real>* pt, const CGL::Point3<Real>& p, CGL::Point3<Real>& clsp)
{
	clsp = *pt;
	CGL::Point3<Real> q = *pt;
	Real a, b;
	a = p[0] - q[0];
	b = a * a;
	a = p[1] - q[1];
	b += a * a;
	a = p[2] - q[2];
	b += a * a;
	return sqrt( b );
}

///
/// Intersection test between a box and a point in 3D
///
template <class Real>
bool checkIntersection (const CGL::BoundingBox3<Real>& box, Surfel<Real>* s) {
	return s->Center().x() >= box.xmin() && s->Center().x() < box.xmax() &&
	s->Center().y() >= box.ymin() && s->Center().y() < box.ymax() &&
	s->Center().z() >= box.zmin() && s->Center().z() < box.zmax();
}

/// Returns the euclidean distance between a point and a point in 3D space
/// @param pt given point.
/// @param p given point.
/// @param clsPt closest point on object.
/// @return distance between p and the polygon.
template <class Real>
Real distance2Item (const Surfel<Real>* st, const CGL::Point3<Real>& s, CGL::Point3<Real>& clsp)
{
	clsp = st->Center();
	CGL::Point3<Real> q = st->Center();
	Real a, b;
	a = s[0] - q[0];
	b = a * a;
	a = s[1] - q[1];
	b += a * a;
	a = s[2] - q[2];
	b += a * a;
	return sqrt( b );
}


}



#endif
