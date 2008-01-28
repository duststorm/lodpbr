#ifndef __CGALTYPESH__

#define __CGALTYPESH__



#include <CGAL/Cartesian.h>
//#include <CGAL/Polyhedron_3.h>
//#include <CGAL/IO/Polyhedron_iostream.h>

typedef double							Number; 	// Number type
typedef CGAL::Cartesian<Number>         K;      	///< Kernel
typedef CGAL::Point_2<K>				Point2;  	// Point in 2D
typedef CGAL::Point_3<K>                Point3;  	///< Point in 3D
typedef CGAL::Vector_2<K> 				Vector2; 	// Vector in 3D
typedef CGAL::Vector_3<K> 				Vector3; 	// Vector in 3D
typedef CGAL::Plane_3<K> 				Plane3; 	// Plane in 3D
typedef CGAL::Bbox_3					BBox;		// A BBox
//typedef Box_3<K>  			    Box3;       // A 3D Box (from octree)
typedef CGAL::Triangle_3<K> 			Triangle3; 	// Triangle in 3D
typedef CGAL::Sphere_3<K> 				Sphere3; 	// Sphere
typedef CGAL::Triangle_2<K> 			Triangle2; 	// Triangle in 3D
typedef CGAL::Line_3<K> 				Line3; 		// Plane in 3D
typedef CGAL::Segment_2<K> 				Segment2; 	// Segment in 2D
typedef CGAL::Segment_3<K> 				Segment3; 	// Segment in 2D
typedef CGAL::Direction_2<K> 			Direction2; 	// Direction in 2D
typedef CGAL::Direction_3<K> 			Direction3; 	// Direction in 3D
typedef CGAL::Object					Objeto;		// A object
typedef CGAL::Aff_transformation_3<K> 	Transformation3;

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

typedef list<Point3> 			PointList;  /// A list of points
typedef vector<Point3> 			PointSet; 	/// Point collection
typedef vector<Number> 			ValueSet; 	/// Value collection

#endif

