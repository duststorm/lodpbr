#ifndef CAMERA_HPP_
#define CAMERA_HPP_


#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Trackball.hpp"
#include "Quaternion.hpp"

/*!
*@class Camera
*@brief Class that represent a dense 4x4 Matrix and Homogeneous Coordinate ..
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@todo OpenGL interface and a C style array, Why MakeView ans MakeProjection dont need The Transpose?
*@todo Não deu certo integrar por que minha nova 3x3 e 4x4 matrix estavam colum major , por isso dava dando bugs ...
* por que eu tava armazenando em 16 variáveis e não mais nuam [][] like , e tava ido direto para colum major 
*@ resolvi o reverso depois de por assim (worldAhead * mZoomRadius) - mWorldLookAt ;   
*/      

namespace CGL{
    class Camera
    {
    public:
    	
    	typedef CGL::Matrix4x4<float> Matrix4x4;
    	typedef CGL::Vector4<float> Vector4;
    	typedef CGL::Vector3<float> Vector3;
    	typedef Trackball<float> Trackball;
    	
        Camera()
        {
        	mZoomRadius =  5.0f;
        	mMinRadius  =  1.0f;
        	mMaxRadius  = 10.0f;
        	
        	mInitalPosition = Vector3(0.0,0.0,0.0);
        	mPosition = Vector3(0.0,0.0,0.0);
        	mEyes = Vector3(0.0,0.0,1.0);
        	mUp = Vector3(0.0,1.0,0.0);
        	mTrackball = Trackball();
        	
        	mFieldOfView = 90.0;
        	mAspectRatio = 1.0f;
        	mZNearPlane  = 0.001f;
        	mZFarPlane   = 1000.0f;
        };
        
        void MoveForward( float Distance )
        {
        	mPosition +=  ( (mPosition - (mEyes )) * Distance);
        }

        void StrafeRight ( float Distance )
        {
                    
        	mPosition +=  ( ((mPosition - (mEyes ))^mUp) *Distance);
        }

        void MoveUpward( float Distance )
        {
        	mPosition = mPosition + (Vector3(0.0,1.0,0.0)*Distance);
        }

        Matrix4x4 ViewMatrix()
        {
            
                // Get the inverse of the arcball's rotation matrix
        		CGL::Quaternion<float> cameraRotation = ~mTrackball.Orientation();
           		
        		       		
                // Transform vectors based on camera's rotation matrix
               // mUp   = cameraRotation.Rotate(Vector3(0,1,0));
                mEyes = cameraRotation.Rotate(Vector3(0,0,1)); 
                               
                mEyes =    mPosition - (mEyes * mZoomRadius);
         
                // Update the eye point based on a radius away from the lookAt position
               // mEyes = cameraRotation.Rotate(mEyes);

                return Matrix4x4 (mEyes, mPosition, mUp);
            
        }
        
//        void Camera::rotateFirstPerson(float headingDegrees, float pitchDegrees)
//        {
//            // Implements the rotation logic for the first person style and
//            // spectator style camera behaviors. Roll is ignored.
//
//            m_accumPitchDegrees += pitchDegrees;
//
//            if (m_accumPitchDegrees > 90.0f)
//            {
//                pitchDegrees = 90.0f - (m_accumPitchDegrees - pitchDegrees);
//                m_accumPitchDegrees = 90.0f;
//            }
//
//            if (m_accumPitchDegrees < -90.0f)
//            {
//                pitchDegrees = -90.0f - (m_accumPitchDegrees - pitchDegrees);
//                m_accumPitchDegrees = -90.0f;
//            }
//
//            Quaternion rot;
//
//            // Rotate camera about the world y axis.
//            // Note the order the quaternions are multiplied. That is important!
//            if (headingDegrees != 0.0f)
//            {
//                rot.fromAxisAngle(WORLD_YAXIS, headingDegrees);
//                m_orientation = rot * m_orientation;
//            }
//
//            // Rotate camera about its local x axis.
//            // Note the order the quaternions are multiplied. That is important!
//            if (pitchDegrees != 0.0f)
//            {
//                rot.fromAxisAngle(WORLD_XAXIS, pitchDegrees);
//                m_orientation = m_orientation * rot;
//            }
//        }

        Matrix4x4 ProjectionMatrix()
        {
          
          
                return mProjectionMatrix;
            
        }

        Vector3 Position()
        {
                        
                return mPosition;
            
        }
        Vector3 Eyes()
        {
                        
                return mEyes;
            
        }

        float FieldOfView()
        {
   
                return mFieldOfView;
                
        }
        
        void SetFieldOfView( const float& pFieldOfView)
        {
            SetProjectionMatrix(pFieldOfView, mAspectRatio, mZNearPlane, mZFarPlane);
        }

        float AspectRatio()
        {
            
        	return mAspectRatio;
        
        }

        void SetAspectRatio( const float& pAspectRatio)
        {
            SetProjectionMatrix( mFieldOfView, pAspectRatio, mZNearPlane, mZFarPlane);
        }
        
        float ZNearPlane()
        {
            
                return mZNearPlane;
                       
        }
        
        void SetZNearPlane(const float& pZNearPlane)
        {
        	SetProjectionMatrix(mFieldOfView, mAspectRatio, pZNearPlane, mZFarPlane);
        }

        float ZFarPlane()
        {
            
                return mZFarPlane;
                       
        }
        
        void SetZFarPlane(const float& pZFarPlane)
        {
        	SetProjectionMatrix(mFieldOfView, mAspectRatio, mZNearPlane, pZFarPlane);
        }

        void SetProjectionMatrix(float pFieldOfView, float pAspectRatio, float pZNearPlane, float pZFarPlane)
        {
            mFieldOfView = pFieldOfView;
            mAspectRatio = pAspectRatio;
            mZNearPlane  = pZNearPlane;
            mZFarPlane   = pZFarPlane;
            mProjectionMatrix = mProjectionMatrix.MakeProjectionMatrix(mFieldOfView, mAspectRatio, mZNearPlane, mZFarPlane);
        }


        void TranslateU(float delta)
        {
            Translate(delta, 0.0f, 0.0f);
        }

        void TranslateV(float delta)
        {
            Translate(0.0f, delta, 0.0f);
        }

        void TranslateN(float delta)
        {
            Translate(0.0f, 0.0f, delta);
        }

        void Translate(Vector3 deltaUVN)
        {
//            Matrix4x4 mat = mTranslationMatrix.MakeTranslate(deltaUVN);
//            mTranslationMatrix = mTranslationMatrix * mat;
//
//            float amount = deltaUVN.length();
//
//            deltaUVN.normalize();
//
////            Matrix4x4 invCameraRot = mTrackball.To4x4RotationMatrix().Inverse();
////            deltaUVN = invCameraRot * deltaUVN;
//
//            mPosition += deltaUVN * amount;
        	
        	// Strafing is quite simple if you understand what the cross product is.
        	// Unlike the dot product, which yields a scalar and is commutative, the vector cross product yields a
            // 3D vector and is not commutative.For example,assume we have two vectors
        	// 
        	//[x1 ,y1, z1] * [x2 , y2 , z2] = [y1z2-z1y2 , z1x2-x1z2 , x1y2-y1x2]
        	//[ 2 , 7 , 3] * [ 1 , 4  , 3] =  [(7)(3)-(3)(4),(3)(1)-(2)(3),(2)(1)-(7)(1)]=[9 ,-3 ,-5]
        	// When dot product and cross product are used together, the cross product takes precedence: a·b×c = a·(b×c)
            
        	// Initialize a variable for the cross product result
        	Vector3 vCross;

        	// Get the view vVector of our camera and store it in a local variable
        	Vector3 View_Vector = mEyes - mPosition;

        	// Here we calculate the cross product of our up vVector and view vVector

        	// The X value for the vVector is:  (V1.y * V2.z) - (V1.z * V2.y)
        	
        	vCross = mUp ^ View_Vector;
        	
        	// Now we want to just add this new vVector to our position and view, as well as
        	// multiply it by our speed factor.  

        	// Add the resultant vVector to our position
        	mPosition[0] += vCross.x() * deltaUVN[0];
        	//mPosition[0] += vCross.z() * deltaUVN[0];
//        	mPosition[2] += vCross.z() * deltaUVN[0];

        	// Add the resultant vVector to our view
        	mEyes[0] += vCross.x() * deltaUVN[0];
  //      	mEyes[2] += vCross.z() * deltaUVN[0];
        	
        	mEyes.normalize();
        	
        }

        void Translate(float deltaU, float deltaV, float deltaN)
        {
            Translate(Vector3(deltaU, deltaV, deltaN));
        }

        void OnRotationBegin( int x, int y)
        {
            mTrackball.BeginTracking(x,y);
        }
        void OnRotationMove(int x, int y)
        {
            mTrackball.Tracking(x,y);
        }


        void Zoom(float mouseWheelDelta)
        {
            // Change the radius from the camera to the model based on wheel scrolling
            mZoomRadius -= mouseWheelDelta * mZoomRadius * 0.1f;
            mZoomRadius  = std::min ( mMaxRadius, mZoomRadius );
            mZoomRadius  = std::max ( mMinRadius, mZoomRadius );
        }

        void SetWindowSize(int width, int height)
        {   
            mTrackball.SetBounds(width, height);	        
        }

         void Reset()
        {
            mPosition = mInitalPosition;
            mTrackball.Reset();
        }
        
        private:
        	
        	Vector3 mInitalPosition;
        	
        	Vector3 mPosition;
        	Vector3 mEyes;
        	Vector3 mUp;

        	float mZoomRadius;
        	float mMinRadius;
        	float mMaxRadius;

        	Trackball mTrackball;

        	Matrix4x4 mTranslationMatrix;

        	float mFieldOfView ;
        	float mAspectRatio ;
        	float mZNearPlane  ;
        	float mZFarPlane   ;

        	Matrix4x4 mProjectionMatrix;
    };

}

#endif /*CAMERA_HPP_*/
