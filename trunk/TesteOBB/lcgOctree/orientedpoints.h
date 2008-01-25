
#ifndef __ORIENTEDPOINTS_H__
#define __ORIENTEDPOINTS_H__

#include "cgaltypes.h"
#include "tp_interpolation.h"
// ***********************************************************************
/*! \class OrientedPoints
 *  \it criates points with his normals vectors
 *  \author Disney Douglas
 */
// ***********************************************************************

class OrientedPoint {

public:

	OrientedPoint(Point3 p, Number v) {
        point = p;
		value = v;
       // func = rbf;
    }

    Point3	getPoint (void) const
    {
    	return point;
    }

    void setPoint (Point3 p){
    	point = p;
	}

	Number	getValue (void) const
    {
    	return value;
	}

    void setValue (Number v){
    	value = v;
	}



    private:
    Point3		point; // a point in 3D
	Number   	value; // a vector in 3D
	//TPInterpolation func; // function of interpolation
};

#endif
