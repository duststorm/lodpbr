#ifndef __CGAL_TYPES__
#define __CGAL_TYPES__

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/HalfedgeDS_vector.h>

typedef CGAL::Cartesian<float>		K;       ///< Kernel
typedef CGAL::Object				Object;
typedef CGAL::Point_3<K>				Point3;  ///< Point in 3D
typedef CGAL::Line_3<K>				Line3;
typedef CGAL::Plane_3<K>				Plane3;
typedef CGAL::Triangle_3<K>			Triangle3;
typedef CGAL::Vector_3<K>			Vector3;
typedef CGAL::Segment_3<K>			Segment3;

typedef CGAL::Point_2<K>				Point2;  ///< Point in 3D
typedef CGAL::Triangle_2<K>			Triangle2;
typedef CGAL::Segment_2<K>			Segment2;
typedef CGAL::Line_2<K>				Line2;


#endif
