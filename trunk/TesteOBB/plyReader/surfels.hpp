#ifndef SURFELS_HPP_
#define SURFELS_HPP_

/**
 *
 * 
 * Author: Ricardo Marroquim
 *
 * Data created: 02-07-07
 *
 **/

#include <vector>


#include "matrixLibrary/Point3.hpp"
#include "matrixLibrary/Vector3.hpp"



extern "C" 
{
	#include <stdio.h>

	#include <strings.h>

	#include "ply.h"
}

typedef struct Vertex {
  float x,y,z;
  float r,g,b;
  float nx,ny,nz;
  float radius;
  void *other_props;       /* other properties */
} Vertex;

typedef struct Face {
  unsigned char nverts;    /* number of vertex indices in list */
  int *verts;              /* vertex index list */
  void *other_props;       /* other properties */
} Face;


/**
 * Surfel class.
 * A surface element (surfel) is a sample point of the surface.
 * Also known as splats in some implementations.
 * The splat has an elliptical or circular form, and an estimated
 * surface normal at it's center.
 **/


template <class Real > class Surfel
{
 public:
		
	 typedef SLAL::Point3<Real> Point3; 
	 typedef SLAL::Vector3<Real> Vector3;
		 
	 Surfel (const Point3& 	position, 
			 const Vector3& normal, 
			 const Real& 	radius, 
			 unsigned int 	id, 
			 const Real& 	pError)
	 {
		 this->position_ 	= position;
	     this->normal_	 	= normal;
	     this->splatRadius_  = radius;
	     this->ID_ 			= id;
	     this->pError_ 		= pError;
	    
	 };
	
	 Surfel (const Point3& 	position, 
			 const Vector3& normal, 
			 const Real& 	radius, 
			 unsigned int 	id )
	 {
		 this->position_ 		= position;
	     this->normal_ 		= normal;
	     this->splatRadius_ 	= radius;
	     this->ID_ 			= id;
	     this->pError_ 		= static_cast<Real> (0);
	    
	 };
	
    
	   
	 ~Surfel() {};
	
	 const Point3 position () const 
	 { 
		 return  ( this->position_ ) ; 
	 };
	 
	 Real position(const int axis)  const
	 { 
		 return ( this->position_[axis] ); 
	 };
	 
	 void setPosition(const Point3& position) 
	 { 
		 this->positon = Point3(position); 
	 };
	
	 const Vector3 normal(void) const 
	 { 
		 return (this->normal); 
	 };
	 
	 Real normal(int axis) const 
	 { 
		 return ( this->normal_[axis] ); 
	 };
	 
	 void setNormal (const Vector3& normal )
	 { 
		 this->normal_ = Vector3(normal); 
	 };
	
	 unsigned int ID () const 
	 { 
		 return ( this->ID_ ); 
	 };
	 
	 void setID (unsigned int id) 
	 {	
		 this->ID_ = id; 
	 };
	
	 Real radius (void) const 
	 { 
		 return this->splatRadius_; 
	 };
	 
	 void setRadius ( const Real& radius ) 
	 { 
		 this->splatRadius_ = radius; 
	 };
	  
	 Real perpendicularError () const 
	 { 
		 return ( this->pError_ ); 
	 };
	
	  /// I/O operator - output
	 inline friend ostream& operator << (ostream& out, const Surfel &s) 
	 {
	    out << s.id_num << " " << s.p.x() << " " 
	    	<< s.p.y() 	<< " " << s.p.z() << " " 
	       	<< s.r 		<< " " << s.n.x() << " " 
	       	<< s.n.y() 	<< " " << s.n.z();
	    
	    return out;
	 };


	 static void  loadPly (const char * filename, std::vector< Surfel<Real> >& surfels)
	 {
		 		 
		 PlyProperty vert_props[] = { /* list of property information for a vertex */
		   {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
		   {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
		   {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0},
		   {"nx", Float32, Float32, offsetof(Vertex,nx), 0, 0, 0, 0},
		   {"ny", Float32, Float32, offsetof(Vertex,ny), 0, 0, 0, 0},
		   {"nz", Float32, Float32, offsetof(Vertex,nz), 0, 0, 0, 0},
		 };


		 /*** the PLY object ***/

		 static PlyFile *in_ply;
		 static int nverts;
		 static PlyOtherProp *vert_other;
		 
		  FILE *fp = fopen(filename, "r");
		  
		  in_ply = read_ply(fp);

		  int i,j;
		  int elem_count;
		  char *elem_name;
		  
		  for (i = 0; i < in_ply->num_elem_types; i++) 
		  {

		    /* prepare to read the i'th list of elements */
		    elem_name = setup_element_read_ply (in_ply, i, &elem_count);

		    if (equal_strings ("vertex", elem_name)) 
		    {

		      /* create a vertex vector to hold all the vertices */
		      //vlist = (Vertex **) malloc (sizeof (Vertex *) * elem_count);
		      nverts = elem_count;

		      /* set up for getting vertex elements */
		      setup_property_ply (in_ply, &vert_props[0]);
		      setup_property_ply (in_ply, &vert_props[1]);
		      setup_property_ply (in_ply, &vert_props[2]);

		      for (j = 0; j < in_ply->elems[i]->nprops; j++) 
		      {
		    	  PlyProperty *prop;
		    	  prop = in_ply->elems[i]->props[j];
		    	  if (equal_strings ("nx", prop->name))
		    		  setup_property_ply (in_ply, &vert_props[3]);
		    	  if (equal_strings ("ny", prop->name))
		    		  setup_property_ply (in_ply, &vert_props[4]);
		    	  if (equal_strings ("nz", prop->name))
		    		  setup_property_ply (in_ply, &vert_props[5]);
		    	  if (equal_strings ("radius", prop->name))
		    		  setup_property_ply (in_ply, &vert_props[6]);
		      }

		      vert_other = get_other_properties_ply (in_ply, 
							     offsetof(Vertex,other_props));

		      Vertex v;
		      /* grab all the vertex elements */
		      for (j = 0; j < elem_count; j++) 
		      {

		        get_element_ply (in_ply, (void *) &v);

		        Point3 	p (v.x, v.y, v.z);
		        Vector3 n (v.nx, v.ny, v.nz);
			
		    	surfels.push_back ( Surfel<Real> (p, n, static_cast<Real> (v.radius), j) );
		        
		      }
		      
		    } // End if (equal_strings ("vertex", elem_name))
		  }
		  
		  close_ply(in_ply);

	 }
	 
 private:
	  /// Point coordinates
	  Point3 position_;

	  /// Estimated surface normal at point sample

	  Vector3 normal_;
	  
	  /// Splat radius
	  Real splatRadius_;

	  /// Perpendicular error
	  Real pError_;
	  
	  /// An identification number for the surfel
	  unsigned int ID_;
	  
  
	  

};

#endif
