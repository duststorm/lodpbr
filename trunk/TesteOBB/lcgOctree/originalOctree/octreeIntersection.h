#ifndef __OCTREE_INTERSECT__
#define __OCTREE_INTERSECT__

#include "mycgal/polyhedron.h"

/// defines methods dependent on the geometry of the itens into the octree.
namespace lcgOctree {

///
/// Intersection test between a box and a point in 3D
///
template <class K>
bool checkIntersection (const Box_3<K>& box, CGAL::Point_3<K>* p) {
    return p->x() >= box.xmin() && p->x() < box.xmax() &&
           p->y() >= box.ymin() && p->y() < box.ymax() &&
           p->z() >= box.zmin() && p->z() < box.zmax();
}

///
/// Intersection test between a box and a triangle in a 3D facet 
///
template <class K>
bool checkIntersection (const Box_3<K>& box, Facet_handle* f) {
    Triangle3 t((*f)->halfedge()->vertex()->point(),
                (*f)->halfedge()->next()->vertex()->point(),
                (*f)->halfedge()->next()->next()->vertex()->point());
	return do_overlap(box.bbox(), t.bbox());
}

/// Returns the euclidean distance between a point and a point in 3D space
/// @param pt given point.
/// @param p given point.
/// @param clsPt closest point on object.
/// @return distance between p and the polygon.
template <class K>
  double distance2Item (const CGAL::Point_3<K>* pt, const CGAL::Point_3<K>& p, CGAL::Point_3<K>& clsp)
  {
    clsp = *pt;
    CGAL::Point_3<K> q = *pt;
    double a, b;
    a = p[0] - q[0];
    b = a * a;
    a = p[1] - q[1];
    b += a * a;
    a = p[2] - q[2];
    b += a * a;
    return sqrt( b );
}

/// Returns the euclidean distance between a point and a triangle in a 3D facet
/// @param pt given point.
/// @param p given point.
/// @param clsPt closest point on object.
/// @return distance between p and the polygon.
template <class K>
  double distance2Item (const Facet_handle* f, const CGAL::Point_3<K>& p, CGAL::Point_3<K>& clsp)
  {
  	clsp = p;
  	Triangle3 tri((*f)->halfedge()->vertex()->point(),
                 (*f)->halfedge()->next()->vertex()->point(),
                 (*f)->halfedge()->next()->next()->vertex()->point());  	
    double b;
    CGAL::Plane_3<K> s_plane = tri.supporting_plane(); 
    CGAL::Point_3<K> p_proj = s_plane.projection(p);
    if(pointInTriangle(p_proj, tri)){
    	b = squared_distance(p, tri.supporting_plane());    	
    }else{
    	CGAL::Segment_3<K> edge1 (tri[0], tri[1]);
    	CGAL::Segment_3<K> edge2 (tri[1], tri[2]);
    	CGAL::Segment_3<K> edge3 (tri[2], tri[0]);
    	double b1, b2, b3;
    	b1 = CGAL::squared_distance(p, edge1);
    	b2 = CGAL::squared_distance(p, edge2);
    	b3 = CGAL::squared_distance(p, edge3);
    	if((b1 < b2) && (b1 < b3)){
    		p_proj = edge1.supporting_line().projection(p);    		 
    		if(p_proj < edge1.min())
    			p_proj = edge1.min();
    		else if(p_proj > edge1.max())
    			p_proj = edge1.max();
    		b = b1;		
    	}else if(b2 < b3){
    		p_proj = edge2.supporting_line().projection(p);
    		if(p_proj < edge2.min())
    			p_proj = edge2.min();
    		else if(p_proj > edge2.max())
    			p_proj = edge2.max();
    		b = b2;
    	}else{    		
    		p_proj = edge3.supporting_line().projection(p);
    		if(p_proj < edge3.min())
    			p_proj = edge3.min();
    		else if(p_proj > edge3.max())
    			p_proj = edge3.max();
    		b = b3;
    	}		
    }
    clsp = p_proj;
    
    int factor = 1;
    
    //~ if(not s_plane.has_on_positive_side(p)){
    	//~ factor = -1;
    //~ }
    
    CGAL::Vector_3<K> v_dist = p - clsp; // - p;
    CGAL::Vector_3<K> plane_normal = s_plane.orthogonal_vector();//(s_plane.a(), s_plane.b(), s_plane.c());
    
	double cos_ang = (v_dist * plane_normal)/(norm(v_dist) * norm(plane_normal));
    
	if(cos_ang < 0 and cos_ang > -0.0000000001)
	    cos_ang = 0;
    
	if(cos_ang < 0){
		factor = -1;
	}
    
    return factor * sqrt( b );
}

/// Computes norm of vector
/// @param v given vector
inline double norm(CGAL::Vector_3<Kernel> v){
   	return (sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
}

/// Verify if two points of segment1 in same side of segment 2
/// @param p1 segment1 begin
/// @param p2 segment1 end
/// @param a segment2 begin
/// @param b segment1 end
inline bool sameSide(Point3 p1, Point3 p2, Point3 a, Point3 b){
	Vector3 cp1 = cross_product(b - a, p1 - a);
	Vector3 cp2 = cross_product(b - a, p2 - a);
	if ((cp1 * cp2) >= -0.0000000001)
		return true;
	else
		return false;
}

/// Verify if point is in triangle
/// @param p point to test
/// @param tri triangle to test
inline bool pointInTriangle(Point3 p, Triangle3 tri){
    if (sameSide(p, tri[0], tri[1], tri[2]) and
	   sameSide(p, tri[1], tri[0], tri[2]) and
	   sameSide(p, tri[2], tri[0], tri[1]))
		return true;
    else
		return false;
}

}



#endif
