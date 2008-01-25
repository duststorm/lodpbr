#ifndef __OCTREE_BOX__
#define __OCTREE_BOX__

#include "cgaltypes.h"


namespace lcgOctree {

///
/// Simple templated max operator
///
template <class K>
inline K OctMAX(const K& a, const K& b) {
  return (a<b)? b:a;
}

///
/// Simple templated min operator
///
template <class K>
inline K OctMIN (const K& a, const K& b) {
  return (a<b)? a:b;
}

/// Returns the euclidean distance between two points.
/// @param q First point.
/// @param p Second point.
/// @return Distance between p and q.
template <class K>
double distance(const CGAL::Point_3<K>& q, const CGAL::Point_3<K>& p)
{
    double a, b;
    a = p[0] - q[0];
    b = a * a;
    a = p[1] - q[1];
    b += a * a;
    a = p[2] - q[2];
    b += a * a;
    return sqrt( b );
}

};

///
/// A class describing the geometry of an octant
///
template <class K>
class Box_3 : public CGAL::Iso_cuboid_3<K> {

public:

typedef typename CGAL::Point_3<K> Point3;
typedef typename CGAL::Iso_cuboid_3<K> Iso_cuboid_3;

/// Constructor
/// @param p1 first corner of box
/// @param p2 second corner of box
Box_3 (const Point3& p1, const Point3& p2) : Iso_cuboid_3 (p1, p2) {};

/// Returns the box corresponding to the suboctant of this box corresponding to
/// son sonIndex
/// @param sonIndex index of the son octant (between 0 and 7)
/// @return box corresponding to the suboctant
Box_3 coords (int sonIndex) const {
     Point3 p1 = min();
     Point3 p2 = max();
     double son_min[3], son_max[3];
     double middle[3] = {(p1[0] + p2[0])/2, (p1[1] + p2[1])/2, (p1[2] + p2[2])/2};

     int mult = 1;
     for (int d = 0; d < 3 ; d++){
         if ((sonIndex & mult) == 0) {
             son_min[d] = p1[d];
             son_max[d] = middle[d];
         }
         else {
             son_min[d] = middle[d];
             son_max[d] = p2[d];
         }
         mult *= 2;
     }
     return Box_3 (Point3(son_min[0], son_min[1], son_min[2]), Point3(son_max[0], son_max[1], son_max[2]));
}

///
/// Checks whether a point is inside this box.
/// @param p given point.
/// @return whether the box contains the point.
///
bool intersect (const Point3& p) const {
    return p.x() >= this->xmin() && p.x() < this->xmax() &&
           p.y() >= this->ymin() && p.y() < this->ymax() &&
           p.z() >= this->zmin() && p.z() < this->zmax();
}

///
/// Intersection test between this and a given box in 3D
/// @param box2 given box.
/// @return whether the boxes do intersect.
///
bool intersect (const Box_3& box2) const {

  Point3 Amin = this->min();
  Point3 Amax = this->max();

  Point3 Bmin = box2.min();
  Point3 Bmax = box2.max();

  return lcgOctree::OctMAX (Amin.x(), Bmin.x()) < lcgOctree::OctMIN(Amax.x(), Bmax.x()) &&
         lcgOctree::OctMAX (Amin.y(), Bmin.y()) < lcgOctree::OctMIN(Amax.y(), Bmax.y()) &&
         lcgOctree::OctMAX (Amin.z(), Bmin.z()) < lcgOctree::OctMIN(Amax.z(), Bmax.z());
}

///
/// Intersection test between a sphere and a given box in 3D
/// @param box given box.
/// @param Center of the sphere
/// @param Raius of the sphere
/// @return whether the boxes intersect the sphere.
///
/*
bool intersect (const Sphere3& sphere) const {
    Point3 Pmin = this->min();
  	Point3 Pmax = this->max();
    Point3 c; // the center of the cube
    double r = distance (Pmax, Pmin)/2; // Semi-diagonal of the cube
    c.x() = Pmax.x() + Pmin.x() /2; // x coordinate of the center of the cube
    c.y() = Pmax.y() + Pmin.y() /2; // It coordinated y of the center of the cube
    c.z() = Pmax.z() + Pmin.z() /2; // It coordinated z of the center of the cube
    return distance(Center, c) < Raius+r;
}

*/
///
/// Returns the four coordinates of one of the six faces of this box.
/// @param plId face identifier.
/// @param pts  face coordinates.
/// @param normal face normal.
///
void getFaceCoordinates(int plId, Point3* pts, Point3& normal) const
{
  switch (plId)
  {
    case 0:
      pts[0] = Point3(this->min()[0], this->min()[1], this->min()[2]);
      pts[1] = Point3(this->min()[0], this->max()[1], this->min()[2]);
      pts[2] = Point3(this->max()[0], this->max()[1], this->min()[2]);
      pts[3] = Point3(this->max()[0], this->min()[1], this->min()[2]);
      normal = Point3(0.0 ,0.0, 1.0);
      break;
    case 1:
      pts[0] = Point3(this->min()[0], this->min()[1], this->max()[2]);
      pts[1] = Point3(this->min()[0], this->max()[1], this->max()[2]);
      pts[2] = Point3(this->max()[0], this->max()[1], this->max()[2]);
      pts[3] = Point3(this->max()[0], this->min()[1], this->max()[2]);
      normal = Point3(0.0 ,0.0, -1.0);
      break;
    case 2:
      pts[0] = Point3(this->min()[0], this->min()[1], this->min()[2]);
      pts[1] = Point3(this->min()[0], this->max()[1], this->min()[2]);
      pts[2] = Point3(this->min()[0], this->max()[1], this->max()[2]);
      pts[3] = Point3(this->min()[0], this->min()[1], this->max()[2]);
      normal = Point3(-1.0 ,0.0, 0.0);
      break;
    case 3:
      pts[0] = Point3(this->max()[0], this->min()[1], this->min()[2]);
      pts[1] = Point3(this->max()[0], this->min()[1], this->max()[2]);
      pts[2] = Point3(this->max()[0], this->max()[1], this->max()[2]);
      pts[3] = Point3(this->max()[0], this->max()[1], this->min()[2]);
      normal = Point3(1.0 ,0.0, 0.0);
      break;
    case 4:
      pts[0] = Point3(this->min()[0], this->min()[1], this->min()[2]);
      pts[1] = Point3(this->min()[0], this->min()[1], this->max()[2]);
      pts[2] = Point3(this->max()[0], this->min()[1], this->max()[2]);
      pts[3] = Point3(this->max()[0], this->min()[1], this->min()[2]);
      normal = Point3(0.0 ,-1.0, 0.0);
      break;
    case 5:
      pts[0] = Point3(this->min()[0], this->max()[1], this->min()[2]);
      pts[1] = Point3(this->max()[0], this->max()[1], this->min()[2]);
      pts[2] = Point3(this->max()[0], this->max()[1], this->max()[2]);
      pts[3] = Point3(this->min()[0], this->max()[1], this->max()[2]);
      normal = Point3(0.0 ,1.0, 0.0);
      break;
  }
}

/// Returns the euclidean distance between a given point p and this box (the closest point on its surface)
/// @param p given point.
/// @return euclidean distance.
double distance(const Point3& p) const
{
    double clsPt[3]; //closest point on the box's surface to the point p
    for (int i = 0; i < 3; ++i)
    {
        if (p[i] < this->min()[i])
            clsPt[i] = this->min()[i];
        else if (p[i] > this->max()[i])
            clsPt[i] = this->max()[i];
        else
            clsPt[i] = p[i];
    }
    Point3 cls(clsPt[0], clsPt[1], clsPt[2]);
    return lcgOctree::distance ( p, cls );
}

};

#endif
