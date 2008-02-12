/**
 * Splat renderer file io functions
 * Read file format : sls (Bart Adams), normals
 *
 * Author : Ricardo Marroquim
 *
 * Date created : 17-01-2007
 *
 **/


#include "matrixLibrary/Point3.hpp"
#include "matrixLibrary/Vector3.hpp"

#include <vector>

using namespace std;

typedef SLAL::Point3<double> Point;
typedef SLAL::Vector3<double> Vector;

extern "C" {
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

char *elem_names[] = { /* list of the kinds of elements in the user's object */
  "vertex", "face"
};

PlyProperty vert_props[] = { /* list of property information for a vertex */
  {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
  {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
  {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0},
  {"nx", Float32, Float32, offsetof(Vertex,nx), 0, 0, 0, 0},
  {"ny", Float32, Float32, offsetof(Vertex,ny), 0, 0, 0, 0},
  {"nz", Float32, Float32, offsetof(Vertex,nz), 0, 0, 0, 0},
  {"radius", Float32, Float32, offsetof(Vertex,radius), 0, 0, 0, 0},
};

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

PlyProperty face_props[] = { /* list of property information for a face */
  {"vertex_indices", Int32, Int32, offsetof(Face,verts),
   1, Uint8, Uint8, offsetof(Face,nverts)},
};


/*** the PLY object ***/

static PlyFile *in_ply;
static int nverts, nfaces;
/* static Vertex **vlist; */
/* static Face **flist; */
static PlyOtherProp *vert_other, *face_other;


void readPly (const char *filename, vector<Surfel<double> > *surfels) {

  FILE *fp = fopen(filename, "r");
  in_ply = read_ply(fp);

  int i,j;
  int elem_count;
  char *elem_name;
  
  for (i = 0; i < in_ply->num_elem_types; i++) {

    /* prepare to read the i'th list of elements */
    elem_name = setup_element_read_ply (in_ply, i, &elem_count);

    if (equal_strings ("vertex", elem_name)) {

      /* create a vertex vector to hold all the vertices */
      //vlist = (Vertex **) malloc (sizeof (Vertex *) * elem_count);
      nverts = elem_count;

      /* set up for getting vertex elements */
      setup_property_ply (in_ply, &vert_props[0]);
      setup_property_ply (in_ply, &vert_props[1]);
      setup_property_ply (in_ply, &vert_props[2]);

      for (j = 0; j < in_ply->elems[i]->nprops; j++) {
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
      for (j = 0; j < elem_count; j++) {

        get_element_ply (in_ply, (void *) &v);

	SLAL::Point3<double> p (v.x, v.y, v.z);
	SLAL::Vector3<double> n (v.nx, v.ny, v.nz);
	
	surfels->push_back ( Surfel<double> (p, n, (double)v.radius, j) );
      }
    }

  }
  close_ply(in_ply);
}

