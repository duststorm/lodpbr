#ifndef LAL_CAMERA_HPP_
#define LAL_CAMERA_HPP_


#include "math/Matrix4x4.hpp"
#include "math/Vector3.hpp"
#include "math/Vector4.hpp"
#include "Scene/Trackball.hpp"
#include "math/Quaternion.hpp"

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
        	mZoomRadius = 0.0f;
        	mMinRadius  = 1.0f;
        	mMaxRadius  = 10.0f;

        	mInitalPosition = Vector3(0.0,0.0,0.0);

        	mOrientation = Quaternion(1.0,0.0,0.0,0.0);
        	mAccumPitchDegrees = 0.0f;
        	mBehavior = FIRST_PERSON;

        	mPosition = Vector3(0.0,0.0,-1.0);
        	mEyes = Vector3(0.0,0.0,0.0);
        	mUp = Vector3(0.0,1.0,0.0);
        	mTrackball = Trackball();

        	mFieldOfView = 90.0;
        	mAspectRatio = 1.0f;
        	mNearPlane  = 0.001f;
        	mFarPlane   = 1000.0f;

        };

        void MoveForward( float Distance )
        {
        	mPosition +=  ( (mPosition - (mEyes )) * Distance);
        }

        void MoveUpward( float Distance )
        {
        	mPosition = mPosition + (mEyes*Distance);
        }

        void StrafeRight ( float Distance )
        {

        	mPosition +=  ( ((mPosition - (mEyes ))^mUp) *Distance);
        }

        Matrix4x4 ViewMatrix()
        {

                // Get the inverse of the arcball's rotation matrix
        		//LAL::Quaternion<float> cameraRotation = ~mTrackball.orientation();

                // Transform vectors based on camera's rotation matrix
        		mUp = mOrientation.Rotate(Vector3::UNIT_Y);

        		mEyes = mOrientation.Rotate(Vector3::UNIT_Z);

              	mEyes =  (mEyes * mZoomRadius) - mPosition;

                // Update the eye point based on a radius away from the lookAt position
               // mEyes = cameraRotation.Rotate(mEyes);

                return Matrix4x4::MakeViewMatrix(mEyes, mPosition, mUp);

        }

        Matrix4x4 ViewMatrixNormal()
        {

        	return Matrix4x4::MakeViewMatrix(mEyes, mPosition, mUp);

        }

        Matrix4x4 ViewMatrix( Vector3& pEyes, Vector3& pPosition, Vector3& pUp )
        {
        	return Matrix4x4::MakeViewMatrix(pEyes, pPosition, pUp);
        }


        Matrix4x4 PespectiveProjectionMatrix()
        {
                return mPespectiveProjectionMatrix;
        }

        Matrix4x4 OrthographicProjectionMatrix()
        {
                return mOrthographicProjectionMatrix;
        }

        Vector3 Position()
        {
        	return mPosition;
        }

        void SetPosition( const Vector3& pPosition)
        {
        	mPosition = pPosition;
        }

        Vector3 Eyes()
        {
        	return mEyes;

        }

        void SetEyes( const Vector3& pEyes )
        {
        	 mEyes = pEyes;
        }

        Vector3 Up()
        {
        	return mUp;
        }

        void SetUp( const Vector3& pUp )
        {
        	mUp = pUp;
        }


        float FieldOfView()
        {
        	return mFieldOfView;
        }

        void SetFieldOfView( const float& pFieldOfView)
        {
        	mFieldOfView = pFieldOfView;
            SetProjectionMatrix(pFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
        }

        float AspectRatio()
        {
        	return mAspectRatio;
        }

        void SetAspectRatio( const float& pAspectRatio)
        {
            SetProjectionMatrix( mFieldOfView, pAspectRatio, mNearPlane, mFarPlane);
        }

        float NearPlane()
        {
        	return mNearPlane;
        }

        void SetNearPlane(const float& pNearPlane)
        {
        	SetProjectionMatrix(mFieldOfView, mAspectRatio, pNearPlane, mFarPlane);
        }

        float FarPlane()
        {
        	return mFarPlane;
        }

        void SetFarPlane(const float& pFarPlane)
        {
        	SetProjectionMatrix(mFieldOfView, mAspectRatio, mNearPlane, pFarPlane);
        }

        void SetProjectionMatrix(float pFieldOfView, float pAspectRatio, float pNearPlane, float pFarPlane)
        {
            mFieldOfView = pFieldOfView;

            mAspectRatio = pAspectRatio;
            mNearPlane  = pNearPlane;
            mFarPlane   = pFarPlane;

            mPespectiveProjectionMatrix = Matrix4x4::MakePespectiveProjectionMatrix(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
        }

        void SetProjectionMatrix (const float& left, const float& right,const float& bottom, const float& top, const float& near, const float& far)
        {
        	mLeft        = left;
        	mRight       = right;
        	mBottom      = bottom;
        	mTop         = top;

            mNearPlane  = near;
            mFarPlane   = far;

            mOrthographicProjectionMatrix = Matrix4x4::MakeOrthographicProjectionMatrix(mLeft,mRight,mBottom,mTop,mNearPlane,mFarPlane);
        }

        void OnRotationBegin( int x, int y)
        {
            mTrackball.BeginTracking(x,y);

        }
        void OnRotationMove(int x, int y)
        {
            mTrackball.Tracking(x,y);
            mOrientation = ~mTrackball.Orientation();
        }

        void Rotate(float headingDegrees, float pitchDegrees, float rollDegrees)
        {
            // Rotates the camera based on its current behavior.
            // Note that not all behaviors support rolling.

            pitchDegrees = -pitchDegrees;
            headingDegrees = -headingDegrees;
            rollDegrees = -rollDegrees;

            switch (mBehavior)
            {
            case FIRST_PERSON:
                RotateFirstPerson(headingDegrees, pitchDegrees);
                break;

            case FLIGHT:
                RotateFlight(headingDegrees, pitchDegrees, rollDegrees);
                break;
            }


        }

        void RotateFlight(float headingDegrees, float pitchDegrees, float rollDegrees)
        {
            // Implements the rotation logic for the flight style camera behavior.

            Quaternion rot;

            rot.FromHeadPitchRoll(headingDegrees, pitchDegrees, rollDegrees);
            mOrientation *= rot;
        }

        void RotateFirstPerson(float headingDegrees, float pitchDegrees)
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

        void SetBehavior(CameraBehavior newBehavior)
        {
            if (mBehavior == FLIGHT and newBehavior == FIRST_PERSON)
            {
                // Moving from flight-simulator mode to first-person.
                // Need to ignore camera roll, but retain existing pitch and heading.

//                lookAt(m_eye, m_eye + m_zAxis.inverse(), WORLD_YAXIS);
            }

            mBehavior = newBehavior;
        }

        inline CameraBehavior GetBehavior() const
        {
        	return mBehavior;
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
        	mWidth = width;
        	mHeight = height;

            mTrackball.SetBounds(width, height);
        }

         void Reset()
        {
            mPosition = mInitalPosition;
            mTrackball.Reset();
        }


    private:

    	Vector3 mInitalPosition;

    	Quaternion mOrientation;
    	float mAccumPitchDegrees;
    	CameraBehavior mBehavior;

    	Vector3 mPosition;
    	Vector3 mEyes;
    	Vector3 mUp;

    	float mWidth;
    	float mHeight;

    	float mZoomRadius;
    	float mMinRadius;
    	float mMaxRadius;

    	Trackball mTrackball;

    	Matrix4x4 mTranslationMatrix;

    	// Pespective
    	float mFieldOfView ;
    	float mAspectRatio ;

    	// Othographic
    	float mLeft;
    	float mRight;
    	float mBottom;
    	float mTop;

    	float mNearPlane  ;
    	float mFarPlane   ;

        Matrix4x4 mPespectiveProjectionMatrix;

        Matrix4x4 mOrthographicProjectionMatrix;
    };

}/* LAL :: NAMESPACE */

#endif /*CAMERA_HPP_*/
