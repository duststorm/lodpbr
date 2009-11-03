#ifndef SURFELS_HPP_
#define SURFELS_HPP_

#include <vector>
#include <algorithm>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component_ocf.h>
#include <vcg/simplex/edge/base.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component_ocf.h>
#include <vcg/simplex/face/topology.h>


#include <wrap/io_trimesh/import_ply.h>
#include <wrap/io_trimesh/export_ply.h>

#include "Math/BoundingBox3.hpp"
#include "Surfel.hpp"



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
struct Bounding_box : public std::unary_function<Celer::Surfel<Real>, void>
{

	Celer::BoundingBox3<Real> box;
    Bounding_box() : box(1e10,1e10,1e10,-1e10,-1e10,-1e10) {}
    void operator()(const Celer::Surfel<Real>& s) {
        box = box + Celer::BoundingBox3<Real>(s.position(0),s.position(1),s.position(2),
        							   		s.position(0),s.position(1),s.position(2));
    }
};


template <class Real >
class SurfelContainer
{
public:

	typedef Celer::Color		 					Color;
	typedef Celer::Point3<Real> 					Point3;
	typedef Celer::Vector3<Real> 					Vector3;
	typedef Celer::BoundingBox3<Real> 			Box3;
	typedef std::vector<Celer::Surfel<Real> > 	Surfels;
	typedef typename Surfels::iterator 			SurfelIterator;


	Surfels mSurfels;

	SurfelContainer(){};

	inline Box3 Box() const
	{
		return ( this->mBox );
	}

	inline void ComputeBox ()
	{
		for (SurfelIterator i = mSurfels.begin(); i != mSurfels.end(); ++i)
		{
			mBox = mBox + Celer::BoundingBox3<Real>(i->Center(0),i->Center(1),i->Center(2),
												  i->Center(0),i->Center(1),i->Center(2));
		}

	}

	static void LoadPly (const char * filename, SurfelContainer<Real>& pSurfels)

	{


		PlyProperty vert_props_color[] = { /* list of property information for a vertex */
		  {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
		  {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
		  {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0},
		  {"r", Float32, Float32, offsetof(Vertex,r), 0, 0, 0, 0},
		  {"g", Float32, Float32, offsetof(Vertex,g), 0, 0, 0, 0},
		  {"b", Float32, Float32, offsetof(Vertex,b), 0, 0, 0, 0},
		  {"nx", Float32, Float32, offsetof(Vertex,nx), 0, 0, 0, 0},
		  {"ny", Float32, Float32, offsetof(Vertex,ny), 0, 0, 0, 0},
		  {"nz", Float32, Float32, offsetof(Vertex,nz), 0, 0, 0, 0},
		  {"radius", Float32, Float32, offsetof(Vertex,radius), 0, 0, 0, 0},
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
		    setup_property_ply (in_ply, &vert_props_color[0]);
		    setup_property_ply (in_ply, &vert_props_color[1]);
		    setup_property_ply (in_ply, &vert_props_color[2]);

		    for (j = 0; j < in_ply->elems[i]->nprops; j++)
		    {
		    	PlyProperty *prop;
		    	prop = in_ply->elems[i]->props[j];
		    	if (equal_strings ("r", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[3]);
		    	if (equal_strings ("g", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[4]);
		    	if (equal_strings ("b", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[5]);
		    	if (equal_strings ("nx", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[6]);
		    	if (equal_strings ("ny", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[7]);
		    	if (equal_strings ("nz", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[8]);
		    	if (equal_strings ("radius", prop->name))
		    		setup_property_ply (in_ply, &vert_props_color[9]);

		      }

		    vert_other = get_other_properties_ply (in_ply,
		    										offsetof(Vertex,other_props));

		    Vertex v;
		      /* grab all the vertex elements */
		    for (j = 0; j < elem_count; j++)
		    {

		      get_element_ply (in_ply, (void *) &v);

		      Point3 	p (v.x, v.y, v.z);
		      Vector3 	n (v.nx, v.ny, v.nz);
		      Color 	c (v.r/255.0, v.g/255.0, v.b/255.0);

		      pSurfels.mSurfels.push_back ( Celer::Surfel<Real> (p,n,c, static_cast<Real> (v.radius), j) );


		     }

		    } // End if (equal_strings ("vertex", elem_name))

		  }
		  pSurfels.ComputeBox();
		  close_ply(in_ply);
	 }

	virtual ~SurfelContainer(){};

private:

	Box3 mBox;

};


#endif /*SURFELS_HPP_*/