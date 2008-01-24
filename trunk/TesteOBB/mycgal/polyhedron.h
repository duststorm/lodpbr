#ifndef __POLYHEDRON
#define __POLYHEDRON
#include <vector>

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>


//#include "cgalTypes.h"
#include "support/id.h"

typedef CGAL::Cartesian<float>		K;       ///< Kernel
typedef CGAL::Point_3<K>				Point3;  ///< Point in 3D
typedef CGAL::Plane_3<K>				Plane3;
typedef CGAL::Triangle_3<K>			Triangle3;
typedef CGAL::Vector_3<K>			Vector3;
typedef CGAL::Segment_3<K>			Segment3;


// An extended bounding box class
struct Bbox : public CGAL::Bbox_3 {
    //Constructor
    Bbox (float x0, float y0, float z0, 
          float x1, float y1, float z1)
        : CGAL::Bbox_3 (x0,y0,z0,x1,y1,z1) {}
    Bbox (const CGAL::Bbox_3& box) 
        : CGAL::Bbox_3 (box) {}
    Bbox () 
        : CGAL::Bbox_3 () {}
    // Point3 at the center of the bounding box
    inline Point3 center () {
        return Point3 ((xmin()+xmax())/2,(ymin()+ymax())/2,(zmin()+zmax())/2);
    }
    // length of the box diagonal
    inline float diameter () {
        Vector3 v (xmax()-xmin(),ymax()-ymin(),zmax()-zmin());
        return sqrt (v.x()*v.x()+v.y()*v.y()+v.z()*v.z());
    }
};

template <class Refs, class Tprev, class Tvertex, class Tface>
class My_halfedge : public CGAL::HalfedgeDS_halfedge_base<Refs,Tprev,Tvertex,Tface> {

 
public:
	
	My_halfedge() 
	{ 
		intersected = false; 
		visible = false;		
		visited = false;
		this->id = ID::nextHalfEdgeID(); 
	}
	
	inline size_t ID() const {  return this->id;  };
	inline void setID (const size_t &id)  { this->id = id; };	
	
	inline void setIntersected (bool intersected) { this->intersected = intersected; };
	inline bool isIntersected () const { return this->intersected; };
		
	inline void setVisible (bool visible) { this->visible = visible; };
	inline bool isVisible () const { return this->visible; };
	
	inline void setVisited (bool visited) { this->visited = visited; };
	inline bool isVisited () const { return this->visited; };
	  
private:
	  
	size_t id;
	bool intersected;
	bool visible;
	bool visited;
  
};


template <class Refs, class Traits, class Plane>
class My_facet 
	: public CGAL::HalfedgeDS_face_base<Refs,Traits, Plane> {
 
public:
	
	typedef typename Refs::Halfedge_handle 	Halfedge_handle;
	
  My_facet() 
  {
	this->id = ID::nextFaceID();
	colorR = 0.0;
	colorG = 0.0;
	colorB = 0.0;
	visible = false;
	visited = false;
	intersected = false;   
  };
  
  
   
  inline bool	operator>(const My_facet& in) 
  {
      
	  return ( this->id > in.ID() );
  }
  
  inline bool	operator<(const My_facet& in) 
  {
      return ( this->id < in.ID() );	  
  }
  
  inline bool	operator==(const My_facet& in) 
  {
      return ( this->id == in.ID() );	  
  }
  
	inline float ColorR() const {  return this->colorR;  };
	inline float ColorG() const {  return this->colorG;  };
	inline float ColorB() const {  return this->colorB;  };
	inline void setColor (const float R , const float G,const float B)  
		{ 	
			this->colorR = R;
			this->colorG = G;
			this->colorB = B;
		};
  
  inline size_t ID() const {  return this->id;  };
  inline void setID (const size_t &id)  { this->id = id; };
     
  inline void setIntersected (bool intersected) { this->intersected = intersected; };
  inline bool isIntersected () const { return this->intersected; };
	
  inline void setVisible (bool visible) { this->visible = visible; };
  inline bool isVisible () const { return this->visible; };
  
  inline void setVisited (bool visited) { this->visited = visited; };
  inline bool isVisited () const { return this->visited; };
  
  inline void setTriangle (Triangle3  triangle) { this->triangle = triangle; };
  inline Triangle3 Triangle () const { return this->triangle; };

  // ---- Edge ---- //
  
  inline void setEdge1 (Segment3  edge) { this->edge1 = edge; };
  inline Segment3 Edge1 () const { return this->edge1; };
  
  inline void setEdge2 (Segment3  edge) { this->edge2 = edge; };
  inline Segment3 Edge2 () const { return this->edge2; };
  
  inline void setEdge3 (Segment3  edge) { this->edge3 = edge; };
  inline Segment3 Edge3 () const { return this->edge3; };
  
  // ---- HalfEdge ---- //
  
  inline void setHalfedge1 (Halfedge_handle halfedge_) { this->halfedge_1 = halfedge_; };
  inline Halfedge_handle  Halfedge1 () const { return this->halfedge_1; };
  
  inline void setHalfedge2 (Halfedge_handle halfedge_) { this->halfedge_2 = halfedge_; };
  inline Halfedge_handle  Halfedge2 () const { return this->halfedge_2; };
  
  inline void setHalfedge3 (Halfedge_handle halfedge_) { this->halfedge_3 = halfedge_; };
  inline Halfedge_handle  Halfedge3 () const { return this->halfedge_3; };
  
  
  
private:
	
	
	Triangle3 triangle;
	
	Segment3 edge1;
	Segment3 edge2;
	Segment3 edge3;
	
	Halfedge_handle  halfedge_1;
	Halfedge_handle	 halfedge_2;
	Halfedge_handle  halfedge_3;
	
	size_t id;
	float colorR;
	float colorG;
	float colorB;
	bool visible;
	bool visited;
	bool intersected;
	

};


// A vertex base with a normal vector and id which it identifies one vertex
template < class Refs  > 
class My_Vertex 
	: public CGAL::HalfedgeDS_vertex_base< Refs, CGAL::Tag_true, Point3> 
{	
public:

   // Must also provide these constructors
    My_Vertex (const Point3& p)
   		: CGAL::HalfedgeDS_vertex_base< Refs, CGAL::Tag_true, Point3> (p) 
   	{
    	this->id = ID::nextVertexID();
    	this->intersected = false;
    	this->valence = 0.0;
    	this->normal = Vector3 (0.0,0.0,0.0);
    	color = Vector3 (1.0,0.0,0.0);
   	}; 
   	My_Vertex ()
   		: CGAL::HalfedgeDS_vertex_base< Refs, CGAL::Tag_true, Point3> () 
   	{
    	this->id = ID::nextVertexID();
    	this->intersected = false;
    	this->valence = 0.0;
    	this->normal = Vector3 (0.0,0.0,0.0);
    	color = Vector3 (1.0,0.0,0.0);
    };
    		
    //list of incident vertex 
    std::vector<size_t> incident_vertex;
   
	inline Vector3 Normal() const {  return this->normal;  };
	 
	inline void setNormal (const Vector3 &normal)  { this->normal = normal; };
	
	inline Vector3 Color() const {  return this->color;  };
	inline void setColor (const Vector3 &color)  { this->color = color; };
	 
	inline float Valence() const {  return this->valence;  };
	inline void addValence() const {  this->valence++;  };
	inline void setValence (const float &valence)  { this->valence = valence; };
	
	inline size_t ID() const {  return this->id;  };
	inline void setID (const size_t &id)  { this->id = id; };
	
	inline bool Intersected() const {  return this->intersected;  };
	inline void setIntersected (const bool intersected)  { this->intersected = intersected; };
	 
private:
	
	   /* Atributes of Vertex */
	
	   // Vertex normal
	   Vector3 normal;
	   
	   /* Color of Vertex */
	   Vector3 color;
	   
	   // valence of vertex 
	   float valence; 
	   
	   // vertex's identification 
	   size_t id;
	   bool intersected;
	
};


// An items type using my vertex.
struct My_items : public CGAL::Polyhedron_items_3 {
	
	template <class Refs, class Traits>
	struct Halfedge_wrapper {
	    typedef My_halfedge<Refs, CGAL::Tag_true, CGAL::Tag_true, CGAL::Tag_true> Halfedge;
	  };
	
    template < class Refs, class Traits>
    struct Vertex_wrapper {
        typedef typename Traits::Point_3 Point;
        typedef My_Vertex <Refs> Vertex;
    };
    
    template <class Refs, class Traits>
    struct Face_wrapper {
      typedef typename Traits::Plane_3  Plane;
      typedef My_facet<Refs, CGAL::Tag_true, Plane> Face;
    };
    
};


///  An extended polyhedron class.
///  . Opengl drawing
///



class Polyhedron : public CGAL::Polyhedron_3<K,My_items>   
{
public:
	
    // Polyhedron bounding box
    Bbox box;
    
    //Octree <K,Facet_handle*> octree;
    
    /// Computes face planes from 3 vertices
    void compute_facet_planes ();
      
    /// Computes a bounding box for the polyhedron
    void compute_box ();
    
    /// Computes a bounding box for the polyhedron
    void compute_vertex_normals ();

    /// Opengl drawing code
    void draw (bool);
        
    /// Opengl drawing points
    void drawPoints();
    
    /// Opengl drawing PolygonWireframe
    void drawPolygonWireframe (bool smooth);
    
    /// Opengl drawing Wireframe
    void drawWireframe (bool smooth);
    
    void drawLine (bool smooth);
    
    // Copy constructor
    Polyhedron (const Polyhedron * p){*this = *p;};
    /// Default constructor
    inline Polyhedron () : CGAL::Polyhedron_3<K,My_items> (){ID::setIDs(0,0,0);};
        
    /// Reads an off model into a polyhedron data structure and returns it
    /// @param filename Name of the file containing model
    /// @return pointer to newly read model or 0 if unsuccessful
    static Polyhedron* load_off (const char * filename);
    
	inline float ColorR() const {  return this->colorR;  };
	inline float ColorG() const {  return this->colorG;  };
	inline float ColorB() const {  return this->colorB;  };
	inline void setColor (const float R , const float G,const float B)  
		{ 	
			this->colorR = R;
			this->colorG = G;
			this->colorB = B;
		};
    
private:
	
	float colorR;
	float colorG;
	float colorB;
	
};


typedef Polyhedron::Facet_iterator		Facet_iterator;
typedef Polyhedron::Halfedge_iterator	Halfedge_iterator;
typedef Polyhedron::Point_iterator		Point_iterator;
typedef Polyhedron::Facet_handle		Facet_handle;
typedef Polyhedron::Halfedge_handle	Halfedge_handle;
typedef Polyhedron::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;
typedef Polyhedron::Facet::Halfedge_around_facet_circulator Halfedge_around_facet_circulator;

#endif
