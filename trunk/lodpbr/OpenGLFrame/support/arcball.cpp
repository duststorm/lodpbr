
/// Coder: Alvaro Cuno - 2006/2007
/// Bugs? e-mail me: alvaroecp@gmail.com

#include "arcball.hpp"

void ArcBall::setBounds(int w, int h) {
   
   assert(w>0 and h>0);
   wfactor = 2.0/(float)w;
   hfactor= 2.0/(float)h;
}

/// It projects a point on the unitary sphere surface
void ArcBall::projectOnSphere(int x, int y, float pProj[]) {
   
   pProj[0] = x*wfactor - 1.0;
   pProj[1] = y*hfactor - 1.0;
   
   float squaredlength = pProj[0]*pProj[0] + pProj[1]*pProj[1]; 
   if (squaredlength>1) { 
      // if the projection point is not over the sphere, then normalize it
      float norma = 1.0/std::sqrt(squaredlength); 
      pProj[0] *= norma;
      pProj[1] *= norma;
      pProj[2]  = 0.0;
   }
   else { // computing the z coordinate of projected point
      pProj[2] = std::sqrt(1.0-squaredlength);
   }
}

void ArcBall::click(int x, int y) {
   
   projectOnSphere(x, y, pIni);
}

void ArcBall::drag(int x, int y, float axis[], float &cosangle) {
   
   projectOnSphere(x, y, pEnd);
   
   // crossproduct(pIni, pEnd)
   cross[0] = pIni[1]*pEnd[2] - pIni[2]*pEnd[1];
   cross[1] = pIni[2]*pEnd[0] - pIni[0]*pEnd[2];
   cross[2] = pIni[0]*pEnd[1] - pIni[1]*pEnd[0];
   
   const float squaredlength = cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2];
   if (squaredlength>1e-5) {
      float norma = 1.0/std::sqrt(squaredlength);
      axis[0] = cross[0]*norma;
      axis[1] = cross[1]*norma;
      axis[2] = cross[2]*norma;
      cosangle = pIni[0]*pEnd[0] + pIni[1]*pEnd[1] + pIni[2]*pEnd[2]; // dotproduct(pIni, pEnd)
   }
   else {
      axis[0]=1.0; axis[1]=axis[2]=0.0; cosangle=1.0; 
   }
}

void ArcBall::drag(int x, int y, float m[]) {
   
   projectOnSphere(x, y, pEnd);
   
   // crossproduct(pIni, pEnd)
   cross[0] = pIni[1]*pEnd[2] - pIni[2]*pEnd[1];
   cross[1] = pIni[2]*pEnd[0] - pIni[0]*pEnd[2];
   cross[2] = pIni[0]*pEnd[1] - pIni[1]*pEnd[0];
   
   const float squaredlength = cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2];
   if (squaredlength>1e-5) {
      float cosangle = pIni[0]*pEnd[0] + pIni[1]*pEnd[1] + pIni[2]*pEnd[2]; // dotproduct(pIni, pEnd)
      // It builts the rotation matrix: quaternion based
      const float l = sqrt(squaredlength + cosangle*cosangle);
      if (l>1e-5) {
         cross[0]/=l; cross[1]/=l; cross[2]/=l; cosangle/=l;
         const float &x = cross[0], &y = cross[1], &z = cross[2], &w = cosangle;
         m[0]=1-2*y*y-2*z*z;  m[4]=2*x*y-2*w*z;    m[8 ]=2*x*z+2*w*y;    m[12]=0.0;
         m[1]=2*x*y+2*w*z;    m[5]=1-2*x*x-2*z*z;  m[9 ]=2*y*z-2*w*x;    m[13]=0.0;
         m[2]=2*x*z-2*w*y;    m[6]=2*y*z+2*w*x;    m[10]=1-2*x*x-2*y*y;  m[14]=0.0;
         m[3]=0.0;            m[7]=0.0;            m[11]=0.0;            m[15]=1.0;
      }
   }
   else { // set the identity matrix
      m[0] = m[5] = m[10] = m[15] = 1.0;
      m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = 
      m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0;
   }
}
