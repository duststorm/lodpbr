#ifndef SURFELS_HPP_
#define SURFELS_HPP_

#include <vector>
#include <algorithm>

#include "slal/BoundingBox3.hpp"
#include "surfel.hpp"

using namespace SLAL;

// For ply Reader
typedef struct Vertex 
{
  float x,y,z;
  float r,g,b;
  float nx,ny,nz;
  float radius;
  void *other_props;       /* other properties */
} Vertex;


/// A function object for computing bounding boxes
template <class Real>
struct Bounding_box : public std::unary_function<Surfel<Real>, void>
{
	
	SLAL::BoundingBox3<Real> box;
    Bounding_box() : box(1e10,1e10,1e10,-1e10,-1e10,-1e10) {}
    void operator()(const Surfel<Real>& s) { 
    	std:: cout << s.position() << std::endl;
        box = box + SLAL::BoundingBox3<Real>(s.position(0),s.position(1),s.position(2),
        				 			   s.position(0),s.position(1),s.position(2));
    }
};


template <class Real >	
class Surfels 
{
public:
	
	typedef SLAL::Point3<Real> Point3;
	typedef SLAL::Vector3<Real> Vector3;
	typedef SLAL::BoundingBox3<Real> Box3; 
	typedef std::vector<Surfel<Real> > surfelContainer;
	typedef typename surfelContainer::iterator surfelIterator;
	
	
	Surfels(){};
	
	inline Box3 box() const
	{
		return ( this->box_ );
	}
	
	inline void compute_box () 
	{
		for (surfelIterator i = surfels.begin(); i != surfels.end(); ++i)
			box_ = box_ + SLAL::BoundingBox3<Real>(i->position(0),i->position(1),i->position(2),
												   i->position(0),i->position(1),i->position(2)); 	
	}
	
	static void loadPly (const char * filename, Surfels<Real>& surfels)
	
	{
		 		 
		PlyProperty vert_props[] = 
		{ /* list of property information for a vertex */
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
			
		      surfels.surfels.push_back ( Surfel<Real> (p, n, static_cast<Real> (v.radius), j) );
		        
		     }
		    
		    } // End if (equal_strings ("vertex", elem_name))
		  
		  }
		  surfels.compute_box();
		  close_ply(in_ply);
	 }
	
	virtual ~Surfels(){};
	
	surfelContainer surfels;
	
private:

	Box3 box_;
	
};

#endif /*SURFELS_HPP_*/
