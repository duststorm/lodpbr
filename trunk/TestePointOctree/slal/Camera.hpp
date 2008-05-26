#ifndef LAL_CAMERA_HPP_
#define LAL_CAMERA_HPP_


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

namespace LAL{
    class Camera
    {
    public:
    	
#ifndef DOXYGEN
    	typedef LAL::Matrix4x4<float> Matrix4x4;
    	typedef LAL::Vector4<float> Vector4;
    	typedef LAL::Vector3<float> Vector3;
    	typedef Trackball<float> Trackball;
#endif
    	
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
        
        void moveForward( float Distance )
        {
        	mPosition +=  ( (mPosition - (mEyes )) * Distance);
        }

        void strafeRight ( float Distance )
        {
                    
        	mPosition +=  ( ((mPosition - (mEyes ))^mUp) *Distance);
        }

        void moveUpward( float Distance )
        {
        	mPosition = mPosition + (Vector3(0.0,1.0,0.0)*Distance);
        }

        Matrix4x4 viewMatrix()
        {
            
                // Get the inverse of the arcball's rotation matrix
        		LAL::Quaternion<float> cameraRotation = ~mTrackball.orientation();
           		
        		       		
                // Transform vectors based on camera's rotation matrix
               // mUp   = cameraRotation.Rotate(Vector3(0,1,0));
                mEyes = cameraRotation.rotate(Vector3(0,0,1)); 
                               
                mEyes =    mPosition - (mEyes * mZoomRadius);
         
                // Update the eye point based on a radius away from the lookAt position
               // mEyes = cameraRotation.Rotate(mEyes);

                return Matrix4x4::makeViewMatrix(mEyes, mPosition, mUp);
            
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

        Matrix4x4 projectionMatrix()
        {
          
          
                return mProjectionMatrix;
            
        }

        Vector3 position()
        {
                        
                return mPosition;
            
        }
        Vector3 eyes()
        {
                        
                return mEyes;
            
        }

        float fieldOfView()
        {
   
                return mFieldOfView;
                
        }
        
        void setFieldOfView( const float& pFieldOfView)
        {
            setProjectionMatrix(pFieldOfView, mAspectRatio, mZNearPlane, mZFarPlane);
        }

        float aspectRatio()
        {
            
        	return mAspectRatio;
        
        }

        void setAspectRatio( const float& pAspectRatio)
        {
            setProjectionMatrix( mFieldOfView, pAspectRatio, mZNearPlane, mZFarPlane);
        }
        
        float zNearPlane()
        {
            
                return mZNearPlane;
                       
        }
        
        void setZNearPlane(const float& pZNearPlane)
        {
        	setProjectionMatrix(mFieldOfView, mAspectRatio, pZNearPlane, mZFarPlane);
        }

        float zFarPlane()
        {
            
                return mZFarPlane;
                       
        }
        
        void setZFarPlane(const float& pZFarPlane)
        {
        	setProjectionMatrix(mFieldOfView, mAspectRatio, mZNearPlane, pZFarPlane);
        }

        void setProjectionMatrix(float pFieldOfView, float pAspectRatio, float pZNearPlane, float pZFarPlane)
        {
            mFieldOfView = pFieldOfView;
            mAspectRatio = pAspectRatio;
            mZNearPlane  = pZNearPlane;
            mZFarPlane   = pZFarPlane;
            mProjectionMatrix = Matrix4x4::makeProjectionMatrix(mFieldOfView, mAspectRatio, mZNearPlane, mZFarPlane);
        }


        void translateU(float delta)
        {
            translate(delta, 0.0f, 0.0f);
        }

        void translateV(float delta)
        {
            translate(0.0f, delta, 0.0f);
        }

        void translateN(float delta)
        {
            translate(0.0f, 0.0f, delta);
        }

        void translate(Vector3 deltaUVN)
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
        	mPosition[0] += vCross.x * deltaUVN[0];
        	//mPosition[0] += vCross.z() * deltaUVN[0];
//        	mPosition[2] += vCross.z() * deltaUVN[0];

        	// Add the resultant vVector to our view
        	mEyes[0] += vCross.x * deltaUVN[0];
  //      	mEyes[2] += vCross.z() * deltaUVN[0];
        	
        	mEyes.normalize();
        	
        }

        void translate(float deltaU, float deltaV, float deltaN)
        {
            translate(Vector3(deltaU, deltaV, deltaN));
        }

        void onRotationBegin( int x, int y)
        {
            mTrackball.beginTracking(x,y);
        }
        void onRotationMove(int x, int y)
        {
            mTrackball.tracking(x,y);
        }


        void zoom(float mouseWheelDelta)
        {
            // Change the radius from the camera to the model based on wheel scrolling
            mZoomRadius -= mouseWheelDelta * mZoomRadius * 0.1f;
            mZoomRadius  = std::min ( mMaxRadius, mZoomRadius );
            mZoomRadius  = std::max ( mMinRadius, mZoomRadius );
        }

        void setWindowSize(int width, int height)
        {   
            mTrackball.setBounds(width, height);	        
        }

         void reset()
        {
            mPosition = mInitalPosition;
            mTrackball.reset();
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

}/* LAL :: NAMESPACE */

#endif /*CAMERA_HPP_*/
