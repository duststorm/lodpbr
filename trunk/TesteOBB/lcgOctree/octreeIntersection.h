#ifndef __OCTREE_INTERSECT__
#define __OCTREE_INTERSECT__

#include "orientedpoints.h"

/// defines methods dependent on the geometry of the itens into the octree.
namespace lcgOctree {



        ///
        /// Intersection test between a box and a face in 3D
        ///
        template <class T>
        bool checkIntersection (const Box_3<T>& box, const OrientedPoint* q)
        {
            return box.intersect(q->getPoint());
        }


        ///
        /// Intersection test between a sphere and a point in 3D
        ///
        template <class T>
        bool checkIntersection (const CGAL::Sphere_3<T>& sphere, const OrientedPoint* q)
        {
			Point3 C = sphere.center();
            Point3 p = q->getPoint();
            double r = sphere.squared_radius();
            double s, d = 0;
            for( int i=0 ; i<3 ; i++ )
            {
				s = C[i] - p[i];
                d += s*s;
            }
            return d <= r;
        }

        //Check to see if the Sphere overlaps a Box
        template <class K>
        bool checkIntersection (const CGAL::Sphere_3<K>& sphere, const Box_3<K>& box)
        {
            Point3 C = sphere.center();
            double r = sphere.squared_radius();
            double s, d = 0;

            //find the square of the distance
            //from the sphere to the box
            for( int i=0 ; i<3 ; i++ )
            {

                if( C[i] < box.min()[i] )
                {

                    s = C[i] - box.min()[i];
                    d += s*s;

                }

                else if( C[i] > box.max()[i] )
                {

                    s = C[i] - box.max()[i];
                    d += s*s;

                }

            }
            return d <= r;

        }

        //Check to see if a Box overlaps the Sphere
        template <class K>
        bool checkIntersection ( const Box_3<K>& box, const CGAL::Sphere_3<K>& sphere)
        {

            return checkIntersection (sphere, box);

        }


        /// Returns the euclidean distance between a point and a polygon in 3D space.
        /// @param face given face.
        /// @param p given point.
        /// @param clsPt closest point on object.
        /// @return distance between p and the polygon.
        template <class T>
        double distance2Item (const OrientedPoint* op, const CGAL::Point_3<T>& p, CGAL::Point_3<T>& clsPt)
        {

        Point3 q = op->getPoint();
            double a, b;
            a = p[0] - q[0];
            b = a * a;
            a = p[1] - q[1];
            b += a * a;
            a = p[2] - q[2];
            b += a * a;

            clsPt = p;

            return sqrt( b );

        }
};
#endif
