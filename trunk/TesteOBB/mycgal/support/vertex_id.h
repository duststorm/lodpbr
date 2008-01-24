#ifndef VERTEX_ID_H_
#define VERTEX_ID_H_

typedef unsigned long long int BigInt;

class Vertex_id
{
private:

	BigInt vertex_id;
	
	static Vertex_id default_id;

public:
	
	inline Vertex_id (BigInt id)
	{
		default_id.vertex_id = id;
	}
	
	inline static BigInt nextId ()
	{
		return ++default_id.vertex_id;
	}
    
    inline static void setId (BigInt id)
    {
    	default_id = Vertex_id (id);
    }
    	
};


#endif /*VERTEX_ID_H_*/
