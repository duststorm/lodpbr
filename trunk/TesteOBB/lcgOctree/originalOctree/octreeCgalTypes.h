#ifndef __OCTREE_CGAL_TYPES__
#define __OCTREE_CGAL_TYPES__

#include "octree.h"

//int limsup = 60;

///CGAL types for octree

typedef CGAL::Cartesian<double> K; ///< Kernel
//typedef CGAL::Point_3<K> Point3;  ///< Point in 3D
typedef Box_3<K> Box3; ///< A 3D Box (from octree)
typedef CGAL::Sphere_3<K> Sphere3; ///< A 3D Sphere

//typedef Octree<K, Point3*, OverflowRefine <K, Point3*, 20> > cgcOctree;
typedef VarOverflowRefine <K, OrientedPoint*> MyRefine;
typedef Octree<K, OrientedPoint*, MyRefine > cgcOctree;
typedef cgcOctree::Iterator cgcOctreeIterator;

typedef OctreeLeafNode <K, OrientedPoint*, OverflowRefine <K, OrientedPoint*,50, 2000> > cgcOctreeLeafNode;
typedef OctreeNode <K, OrientedPoint*, OverflowRefine <K, OrientedPoint*, 50, 2000> > cgcOctreeNode;

#endif
