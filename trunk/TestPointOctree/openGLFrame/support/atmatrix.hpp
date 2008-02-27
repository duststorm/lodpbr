
#ifndef __AFFINETMATRIX_H__
#define __AFFINETMATRIX_H__

/// This class implements a three-dimensional affine 
/// transformation matrix
template <class T>
class AMatrix {
   
public:
   AMatrix() {
      for (unsigned int i=0; i<15; ++i) this->m[i] = 0.0;
      this->m[15] = 1.0;
   }
   
   AMatrix& operator=(const AMatrix& v) {
      for (unsigned int i=0; i<16; ++i) this->m[i] = v.m[i];
      return *this;
   }
   
   /// Composes two affine transformations
   AMatrix operator*(const AMatrix& B) {
      
      AMatrix C;
      const AMatrix &A = *this;
      for (unsigned int i=0; i<4; ++i) {
         for (unsigned int j=0; j<4; ++j) {
            T tmp = 0;
            for (unsigned int k=0; k<4; ++k) tmp += A[k*4+i]*B[j*4+k];
            C[j*4+i] = tmp;
         }
      }
      return C;
   }
   
   /// Sets an identity transformation
   void identity() {
      
      m[1]=m[2]=m[3]=
      m[4]=m[6]=m[7]=
      m[8]=m[9]=m[11]=
      m[12]=m[13]=m[14]=0.0;
      m[0]=m[5]=m[10]=m[15]=1.0;
   }
   
   /// Introduces a translation by a vector (x,y,z)
   void translation(const T x, const T y, const T z) {
      m[12]=x; m[13]=y; m[14]=z;
   }
   
   /// Introduces an uniform scaling by a factor s
   void scaling(const T s) {
      m[0]*=s; m[5]*=s; m[10]*=s;
   }
   
   inline const T* operator&(void) const { return m; }
   T* operator&(void) { return m; }
   
   inline const T& operator[] (unsigned i) const { return m[i]; }
   T& operator[](unsigned i) { return m[i]; }
   
private:
   T m[16];
};


#include <iostream>
// Output operator
template <class T>
std::ostream& operator<<(std::ostream &os, const AMatrix<T> &M) {
   
   for (unsigned int i=0; i<16; ++i) os<<M[i]<<" ";
   return os;
}

#endif
