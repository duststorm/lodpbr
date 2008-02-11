/**
 *
 * 
 * Author: Ricardo Marroquim
 *
 * Data created: 02-07-07
 *
 **/

#ifndef __SURFELS__
#define __SURFELS__

#include <vector>


#include "matrixLibrary/Point3.hpp"
#include "matrixLibrary/Vector3.hpp"

/**
 * Surfel class.
 * A surface element (surfel) is a sample point of the surface.
 * Also known as splats in some implementations.
 * The splat has an elliptical or circular form, and an estimated
 * surface normal at it's center.
 **/
template <class T> class Surfel
{
 public:
 
  Surfel ( const SLAL::Point3<T>& _p, const SLAL::Vector3<T>& _n, T _r, unsigned int _id, T _ep) 
   : p(_p), n(_n), r(_r), ep(_ep), id_num(_id) 
  {
    this->p.RGB( 0.8, 0.4, 0.2 );
  };

  Surfel ( const SLAL::Point3<T>& _p,  const SLAL::Vector3<T>& _n, const T& _r, unsigned int _id) 
   	: p(_p), n(_n), r(_r), id_num(_id), ep(0.0)
  {
	this->p.setRGB( 0.8, 0.4, 0.2 );
  };

  Surfel ( const SLAL::Point3<T>& _p, unsigned int _id) 
  	: p(_p), id_num(_id), ep(0.0)
  {
    n = SLAL::Vector3<T> (0.0, 0.0, 0.0);
    this->p.RGB( 0.8, 0.4, 0.2 );
    r = static_cast< T > (0);
  };

  Surfel( const SLAL::Point3<T>& _p) 
  	: p(_p), ep(0.0)
  {
    n      = SLAL::Vector3<T> ( 0.0, 0.0, 0.0 );
    this->p.RGB( 0.8, 0.4, 0.2 );
    r      = static_cast< T > (0);
    id_num = 0;
  }
  
  ~Surfel() {};

  const SLAL::Point3<T> position(void) const 
  {
	  return p; 
  };
  
  double position(const int axis)  
  { 
	  return p[axis]; 
  };
  
  void setPosition(const SLAL::Point3<T> _p) 
  { 
	  p = SLAL::Point3<T>(_p); 
  };

  const SLAL::Vector3<T> normal(void) const { return n; }
  double normal(int axis) { return n[axis]; }
  void setNormal( SLAL::Vector3<T> _n) { n = SLAL::Vector3<T>(_n); }

  unsigned int id (void) const { return id_num; }
  void setId (unsigned int _id) {id_num = _id; }

  double radius (void) const { return r; }
  void setRadius (double _r) { r = _r; }
  
  double perpendicularError (void) const { return ep; }

  /// I/O operator - output
  inline friend ostream& operator << (ostream& out, const Surfel &s) {
    out << s.id_num << " " << s.p.x() << " " << s.p.y() << " " << s.p.z() << " " << s.r << " "
	<< s.n.x() << " " << s.n.y() << " " << s.n.z();
    return out;
  }

  /// Point coordinates
  SLAL::Point3<T> p;

  /// Estimated surface normal at point sample
  SLAL::Vector3<T> n;
  
  /// Splat radius
  T r;

  /// Perpendicular error
  T ep;

 private:

  /// An identification number for the surfel
  unsigned int id_num;

};


typedef vector<Surfel<double> >::iterator surfelVectorIter;


#endif
