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


class CEdge;
class CFaceO;
class CVertexO;

//Vert Mem Occupancy  --- 40b ---

class CVertexO  : public vcg::VertexSimp2< CVertexO, CEdge, CFaceO,
  vcg::vertex::InfoOcf,           /*  4b */
  vcg::vertex::Coord3f,           /* 12b */
  vcg::vertex::BitFlags,          /*  4b */
  vcg::vertex::Normal3f,          /* 12b */
  vcg::vertex::Qualityf,          /*  4b */
  vcg::vertex::Color4b,           /*  4b */
  vcg::vertex::VFAdjOcf,          /*  0b */
  vcg::vertex::MarkOcf,           /*  0b */
  vcg::vertex::TexCoordfOcf,      /*  0b */
  vcg::vertex::CurvaturefOcf,     /*  0b */
  vcg::vertex::CurvatureDirfOcf,  /*  0b */
  vcg::vertex::RadiusfOcf         /*  0b */
  >{
};


class CEdge : public vcg::EdgeSimp2<CVertexO,CEdge,CFaceO, vcg::edge::EVAdj> {
public:
	inline CEdge(){};
  inline CEdge( CVertexO * v0, CVertexO * v1){ V(0)= v0 ; V(1)= v1;};
  static inline CEdge OrderedEdge(CVertexO* v0,CVertexO* v1){
   if(v0<v1) return CEdge(v0,v1);
   else return CEdge(v1,v0);
	}
};

//Face Mem Occupancy  --- 32b ---

class CFaceO    : public vcg::FaceSimp2<  CVertexO, CEdge, CFaceO,
      vcg::face::InfoOcf,              /* 4b */
      vcg::face::VertexRef,            /*12b */
      vcg::face::BitFlags,             /* 4b */
      vcg::face::Normal3f,             /*12b */
      vcg::face::QualityfOcf,          /* 0b */
      vcg::face::MarkOcf,              /* 0b */
      vcg::face::Color4bOcf,           /* 0b */
      vcg::face::FFAdjOcf,             /* 0b */
      vcg::face::VFAdjOcf,             /* 0b */
      vcg::face::WedgeTexCoordfOcf     /* 0b */
    > {};

class CMeshO    : public vcg::tri::TriMesh< vcg::vertex::vector_ocf<CVertexO>, vcg::face::vector_ocf<CFaceO> > {
public :
	int sfn; //The number of selected faces.
  vcg::Matrix44f Tr; // Usually it is the identity. It is applied in rendering and filters can or cannot use it. (most of the filter will ignore this)
  const vcg::Box3f &trBB() {
	static vcg::Box3f bb;
	bb.SetNull();
	bb.Add(Tr,bbox);
		return bb;
	}
};


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
struct Bounding_box : public std::unary_function<LAL::Surfel<Real>, void>
{

	LAL::BoundingBox3<Real> box;
    Bounding_box() : box(1e10,1e10,1e10,-1e10,-1e10,-1e10) {}
    void operator()(const LAL::Surfel<Real>& s) {
        box = box + LAL::BoundingBox3<Real>(s.position(0),s.position(1),s.position(2),
        							   		s.position(0),s.position(1),s.position(2));
    }
};


template <class Real >
class SurfelContainer
{
public:

	typedef LAL::Color		 					Color;
	typedef LAL::Point3<Real> 					Point3;
	typedef LAL::Vector3<Real> 					Vector3;
	typedef LAL::BoundingBox3<Real> 			Box3;
	typedef std::vector<LAL::Surfel<Real> > 	Surfels;
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
			mBox = mBox + LAL::BoundingBox3<Real>(i->Center(0),i->Center(1),i->Center(2),
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

		      pSurfels.mSurfels.push_back ( LAL::Surfel<Real> (p,n,c, static_cast<Real> (v.radius), j) );


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
