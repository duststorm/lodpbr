#ifndef _ID_H_
#define _ID_H_

#include <stddef.h>


class ID
{
private:

	size_t vertex_id;
	
	size_t face_id;
	
	size_t halfEdge_id;
	
	static ID default_id;

public:

	// default Constructor
	inline ID (size_t id)
	{
		default_id.vertex_id 	= id;
		default_id.face_id 		= id;
	}

	// 
	inline static void setIDs (size_t v_id, size_t f_id, size_t h_id)
	{
		default_id.vertex_id 	= v_id;
		default_id.face_id 		= f_id;
		default_id.halfEdge_id 	= h_id;
	}

	//For vertex id 

	inline static size_t nextVertexID ()
	{
		return ++default_id.vertex_id;
	}

    inline static void setVertexID (size_t id)
    {
    	default_id.vertex_id  = id;
    }

    //For face id
    

	inline static size_t nextFaceID ()
	{
		return ++default_id.face_id;
	}
    
    inline static void setFaceID (size_t id)
    {
    	default_id.face_id = id;
    }
    
    //For halfedge id

	inline static size_t nextHalfEdgeID ()
	{
		return ++default_id.halfEdge_id;
	}
    
    inline static void setHalfEdgeID (size_t id)
    {
    	default_id.halfEdge_id = id;
    }
    	
    	
};


#endif /*VERTEX_ID_H_*/
