
/// Coder: Alvaro Cuno - 2006/2007
/// Bugs? e-mail me: alvaroecp@gmail.com

#ifndef _ARCBALL_H_
#define _ARCBALL_H_

#include <cassert>
#include <cmath>

/// This class implements an arcball for interaction 
/// on 3D space using a 2D mouse
class ArcBall {
   
public:
   
   /// Default constructor.
   ArcBall(): 
      wfactor(1), hfactor(1) { }
   
   /// Constructor.
   /// @param w canvas' width.
   /// @param h canvas' height.
   ArcBall(int w, int h) { 
      assert(w>0 and h>0);
      wfactor = 2.0/(float)w;
      hfactor= 2.0/(float)h;
   }
   
   /// It sets the canvas bounds.
   /// @param w canvas' width.
   /// @param h canvas' height.
   void setBounds(int w, int h);
   
   /// Implements mouse click at given screen position.
   /// @param x coordinate.
   /// @param y coordinate.
   void click(int x, int y);
   
   /// Implements mouse drag to given screen position.
   /// @param x coordinate.
   /// @param y coordinate.
   /// @param axis unitary rotation vector.
   /// @param cosangle angle cosine.
   void drag(int x, int y, float axis[], float &cosangle);
   
   /// Implements mouse drag to given screen position.
   /// @param x coordinate.
   /// @param y coordinate.
   /// @param m transformation matrix.
   void drag(int x, int y, float m[]);
   
private:
   
   /// It projects a point on the unitary sphere surface
   /// @param x coordinate.
   /// @param y coordinate.
   /// @param pProj the projected point
   void projectOnSphere(int x, int y, float pProj[3]);
   
   float   wfactor;     // width ajusted factor 
   float   hfactor;     // height ajusted factor
   
   float   pIni[3];     // the initial vector
   float   pEnd[3];     // the end vector
   float   cross[3];    // cross product of pIni and pEnd
};

#endif
