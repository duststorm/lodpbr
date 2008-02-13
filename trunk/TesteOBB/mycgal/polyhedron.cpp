#include "polyhedron.h"
#include <GL/gl.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>


#include <CGAL/Bbox_3.h>

/// A function object for computing vertex normals 
struct Vertex_normal : public std::unary_function<Polyhedron::Vertex,void>
{
    void operator() (Polyhedron::Vertex& v) {
        Polyhedron::Vertex::Halfedge_around_vertex_const_circulator 
            hbegin = v.vertex_begin(), h = hbegin;
        int n = 0;
        Vector3 sum(0,0,0);
        do {
            if (h->facet() != 0) {
                Vector3 v (h->facet()->plane().orthogonal_vector());
                sum = sum + v;
                n++;
            }
        } while (++h != hbegin);
        assert (n > 0);
        v.setNormal ( sum * (1.0/n) );
        //std::cout << v.normal << std::endl; 
    }
};




// A function object for computing plane equations
struct Plane_equation {
    template <class Facet>
    typename Facet::Plane_3 operator()( Facet& f) {
        typename Facet::Halfedge_handle h = f.halfedge();
                
        Halfedge_handle hn = h->next();
        Halfedge_handle hnn = h->next()->next();
        
        f.setHalfedge1 ( hn );
        f.setHalfedge2 ( hnn );
        f.setHalfedge3 ( h );
        
        f.setEdge1 ( Segment3 (h->vertex()->point(), h->next()->vertex()->point() ) );
        f.setEdge2 ( Segment3 (h->next()->vertex()->point(), h->next()->next()->vertex()->point()) );
        f.setEdge3 ( Segment3 (h->next()->next()->vertex()->point(), h->vertex()->point()) );
        
        f.setTriangle	( Triangle3 ( h->vertex()->point(),
                					 h->next()->vertex()->point(),
                					 h->next()->next()->vertex()->point() )
        				);
        typedef typename Facet::Plane_3 Plane;
        return Plane ( h->vertex()->point(),
                       h->next()->vertex()->point(),
                       h->next()->next()->vertex()->point());
    }
};


/// A function object for computing bounding boxes
struct Bounding_box : public std::unary_function<Point3, void>
{
    Bbox box;
    Bounding_box() : box(1e10,1e10,1e10,-1e10,-1e10,-1e10) {}
    void operator()(const Point3& p) { 
        box = box + Bbox(p[0],p[1],p[2],p[0],p[1],p[2]);
    }
};



/// Computes face planes from 3 vertices
void Polyhedron::compute_facet_planes () {
    std::transform(facets_begin(), facets_end(), planes_begin(),
                   Plane_equation());
}

/// Computes a bounding box for the polyhedron
void Polyhedron::compute_box () {
    box = (std::for_each(points_begin(), points_end(), Bounding_box())).box;
}

/// Computes a bounding box for the polyhedron
void Polyhedron::compute_vertex_normals () {
    std::for_each(vertices_begin(), vertices_end(), Vertex_normal());
}


void Polyhedron::drawPoints() {
   
   glDisable(GL_LIGHTING);		
   glPointSize(5.0);
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_POINTS);
   Vertex_iterator vit = vertices_begin();
   
   while (vit != vertices_end()) {
      const Point3 &p = vit->point();
      glVertex3f(p[0], p[1], p[2]);
      ++vit;
   }
   
   glEnd();
   glEnable(GL_LIGHTING);
   glPointSize(1.0);
}


void Polyhedron::drawPolygonWireframe (bool smooth)
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
          
    	draw(smooth);
          
    glDisable(GL_POLYGON_OFFSET_FILL);
          
    glColor4f(0.1,0.1,0.1,1.0);
    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_LINE_BIT | GL_LIGHTING_BIT);
   
    	 glLineWidth(1.0);
         glDisable(GL_LIGHTING);
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         drawLine(smooth);
          
    glPopAttrib();

}

void Polyhedron::drawWireframe (bool smooth)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);

		glLineWidth(1.0);
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawLine(smooth);
	
	glPopAttrib();
	
}

/// Opengl drawing code
void Polyhedron::draw (bool smooth) {
	
    for (Facet_iterator f = facets_begin(); f != facets_end(); ++f) {
        Facet::Halfedge_around_facet_circulator 
            hbegin = f->facet_begin(), h = hbegin;
        if (f->isIntersected() == true)
        	glColor3f(f->ColorR(),f->ColorG(),f->ColorB());
        else
        	glColor3f(colorR,colorG,colorB);
        glBegin (GL_POLYGON);
        if (!smooth) {
            Vector3 fnormal = f->plane().orthogonal_vector();
            glNormal3f (fnormal[0],fnormal[1],fnormal[2]);
        }
        
        do {
            const Point3& pt = h->vertex()->point();
            if (smooth) {
               Vector3 vnormal (h->vertex()->Normal());
               glNormal3f (vnormal[0],vnormal[1],vnormal[2]);
            }
            glVertex3f (pt[0], pt[1], pt[2]);
        } while (++h != hbegin);
        
        glEnd ();
        
    }
}

void Polyhedron::drawLine (bool smooth) {
    for (Facet_iterator f = facets_begin(); f != facets_end(); ++f) {
        Facet::Halfedge_around_facet_circulator 
            hbegin = f->facet_begin(), h = hbegin;
        glBegin (GL_POLYGON);
        if (!smooth) {
            Vector3 fnormal = f->plane().orthogonal_vector();
            glNormal3f (fnormal[0],fnormal[1],fnormal[2]);
        }
        
        do {
            const Point3& pt = h->vertex()->point();
            if (smooth) {
               Vector3 vnormal (h->vertex()->Normal());
               glNormal3f (vnormal[0],vnormal[1],vnormal[2]);
            }
            glVertex3f (pt[0], pt[1], pt[2]);
        } while (++h != hbegin);
        
        glEnd ();
    }
}

// Opengl drawing code

/*void Polyhedron::draw (bool smooth) {
	
    for (Facet_iterator f = facets_begin(); f != facets_end(); ++f) {
        Facet::Halfedge_around_facet_circulator 
            hbegin = f->facet_begin(), h = hbegin;
       
        glBegin (GL_POLYGON);
        if (!smooth) {
            Vector3 fnormal = f->plane().orthogonal_vector();
            glNormal3f (fnormal[0],fnormal[1],fnormal[2]);
        }
        
        do {
            const Point3& pt = h->vertex()->point();
            if (smooth) {
               Vector3 vnormal (h->vertex()->normal);
               glNormal3f (vnormal[0],vnormal[1],vnormal[2]);
            }
            glVertex3f (pt[0], pt[1], pt[2]);
        } while (++h != hbegin);
        glEnd ();
     
        glDisable (GL_LIGHTING);
        glColor3f (1.0, 0.0, 0.0);
        glBegin (GL_LINE_LOOP);
        do {
                    const Point3& pt = h->vertex()->point();
                    if (smooth) {
                       Vector3 vnormal (h->vertex()->normal);
                       glNormal3f (vnormal[0],vnormal[1],vnormal[2]);
                    }
                    glVertex3f (pt[0], pt[1], pt[2]);
       } while (++h != hbegin);
       glEnd(); 
       glEnable (GL_LIGHTING); 
    }
}
*/
/// Reads an off model into a polyhedron data structure and returns it
/// @param filename Name of the file containing model
/// @return pointer to newly read model or 0 if unsuccessful



Polyhedron* Polyhedron::load_off (const char * filename)
{
    std::fstream off_file (filename, std::ios_base::in);
    if (off_file) {
        Polyhedron * p = new Polyhedron ();
        
        off_file >> *p;
        if (off_file) {
            /*std::cout << "Polyhedral surface has "    
                      << p->size_of_vertices () << " vertices, "
                      << p->size_of_facets () << " facets,";*/

            p->compute_box ();
            p->compute_facet_planes ();
            p->compute_vertex_normals ();   
            
            return p;
            
        }
    }      
    return 0;
}

