#ifndef LAL_CAMERA_HPP_
#define LAL_CAMERA_HPP_


#include "slal/Matrix4x4.hpp"
#include "slal/Vector3.hpp"
#include "slal/Vector4.hpp"
#include "Scene/Trackball.hpp"
#include "slal/Quaternion.hpp"

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
	
    	typedef LAL::Quaternion<float> Quaternion;
    	typedef LAL::Matrix4x4<float> Matrix4x4;
    	typedef LAL::Vector4<float> Vector4;
    	typedef LAL::Vector3<float> Vector3;
    	typedef Trackball<float> Trackball;
   	
    	enum CameraBehavior
    	{
    		FIRST_PERSON,
    		FLIGHT
    	};
    	
        Camera()
        {
        	mZoomRadius =  5.0f;
        	mMinRadius  =  1.0f;
        	mMaxRadius  = 10.0f;
        	
        	mInitalPosition = Vector3(0.0,0.0,0.0);
        	
        	mOrientation = Quaternion(1.0,0.0,0.0,0.0);
        	mAccumPitchDegrees = 0.0f;
        	mBehavior = FIRST_PERSON;
       	
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
        
        void moveUpward( float Distance )
        {
        	mPosition = mPosition + (Vector3::UNIT_Y*Distance);
        }

        void strafeRight ( float Distance )
        {
                    
        	mPosition +=  ( ((mPosition - (mEyes ))^mUp) *Distance);
        }

        Matrix4x4 viewMatrix()
        {
            
                // Get the inverse of the arcball's rotation matrix
        		//LAL::Quaternion<float> cameraRotation = ~mTrackball.orientation();
            	       		       		
                // Transform vectors based on camera's rotation matrix
                //mUp   = mOrientation.rotate(Vector3::UNIT_Y);
                mEyes = mOrientation.Rotate(Vector3::UNIT_Z);
                
                mEyes =    mPosition - (mEyes * mZoomRadius);
         
                // Update the eye point based on a radius away from the lookAt position
               // mEyes = cameraRotation.Rotate(mEyes);

                return Matrix4x4::MakeViewMatrix(mEyes, mPosition, mUp);
            
        }
        

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
            
            mProjectionMatrix = Matrix4x4::MakeProjectionMatrix(mFieldOfView, mAspectRatio, mZNearPlane, mZFarPlane);
        }


        void onRotationBegin( int x, int y)
        {
            mTrackball.beginTracking(x,y);

        }
        void onRotationMove(int x, int y)
        {
            mTrackball.tracking(x,y);
            mOrientation = ~mTrackball.orientation();
        }

        void rotate(float headingDegrees, float pitchDegrees, float rollDegrees)
        {
            // Rotates the camera based on its current behavior.
            // Note that not all behaviors support rolling.

            pitchDegrees = -pitchDegrees;
            headingDegrees = -headingDegrees;
            rollDegrees = -rollDegrees;

            switch (mBehavior)
            {
            case FIRST_PERSON:
                rotateFirstPerson(headingDegrees, pitchDegrees);
                break;

            case FLIGHT:
                rotateFlight(headingDegrees, pitchDegrees, rollDegrees);
                break;
            }


        }

        void rotateFlight(float headingDegrees, float pitchDegrees, float rollDegrees)
        {
            // Implements the rotation logic for the flight style camera behavior.

            Quaternion rot;

            rot.FromHeadPitchRoll(headingDegrees, pitchDegrees, rollDegrees);
            mOrientation *= rot;
        }

        void rotateFirstPerson(float headingDegrees, float pitchDegrees)
        {
            // Implements the rotation logic for the first person style and
            // spectator style camera behaviors. Roll is ignored.

            mAccumPitchDegrees += pitchDegrees;

            if (mAccumPitchDegrees > 90.0f)
            {
                pitchDegrees = 90.0f - (mAccumPitchDegrees - pitchDegrees);
                mAccumPitchDegrees = 90.0f;
            }

            if (mAccumPitchDegrees < -90.0f)
            {
                pitchDegrees = -90.0f - (mAccumPitchDegrees - pitchDegrees);
                mAccumPitchDegrees = -90.0f;
            }

            Quaternion rot;

            // Rotate camera about the world y axis.
            // Note the order the quaternions are multiplied. That is important!
            if (headingDegrees != 0.0f)
            {
                rot.FromAxisAngle(Vector3::UNIT_Y, headingDegrees);
                mOrientation = rot * mOrientation;
            }

            // Rotate camera about its local x axis.
            // Note the order the quaternions are multiplied. That is important!
            if (pitchDegrees != 0.0f)
            {
                rot.FromAxisAngle(Vector3::UNIT_X, pitchDegrees);
                mOrientation = mOrientation * rot;
            }
        }

        void setBehavior(CameraBehavior newBehavior)
        {
            if (mBehavior == FLIGHT and newBehavior == FIRST_PERSON)
            {
                // Moving from flight-simulator mode to first-person.
                // Need to ignore camera roll, but retain existing pitch and heading.

//                lookAt(m_eye, m_eye + m_zAxis.inverse(), WORLD_YAXIS);
            }

            mBehavior = newBehavior;
        }
        
        inline CameraBehavior getBehavior() const
        { 
        	return mBehavior; 
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

    	Quaternion mOrientation;
    	float mAccumPitchDegrees;
    	CameraBehavior mBehavior;

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
