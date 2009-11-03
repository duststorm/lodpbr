#ifndef LAL_CAMERA_HPP_
#define LAL_CAMERA_HPP_


#include "Math/Matrix4x4.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"
#include "Scene/Trackball.hpp"
#include "Math/Quaternion.hpp"

#include <vcg/Eigen/Core>
#include <vcg/Eigen/Geometry>

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

namespace Celer{

    class Camera
    {
    public:

    	typedef Celer::Quaternion<float> Quaternion;
    	typedef Celer::Matrix4x4<float> Matrix4x4;
    	typedef Celer::Vector4<float> Vector4;
    	typedef Celer::Vector3<float> Vector3;
    	typedef Celer::Vector2<int> Vector2;
    	typedef Celer::Trackball<float> Trackball;

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

            pitchDegrees = 0.0f;
            headingDegrees = 0.0f;
            rollDegrees = 0.0f;

            mouseLockedPosition.Set(0,0);
            mousePosition.Set(0,0);
            mouseLocked = 0;

        	mBehavior = FIRST_PERSON;

        	mFocus = Vector3(0.0,0.0,1.0);
        	mEyes = Vector3(0.0,0.0,0.0);
        	mUp = Vector3(0.0,1.0,0.0);
        	mTrackball = Trackball();

        	mViewMatrix.Identity();

        	mFieldOfView = 90.0;
        	mAspectRatio = 1.0f;
        	mNearPlane  = 0.001f;
        	mFarPlane   = 1000.0f;

        }


        Vector3 Focus()
        {
        	return mFocus;
        }

        void SetFocus( const Vector3& pFocus)
        {
        	mFocus = pFocus;
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

        void MoveForward( float Distance )
        {
        	mEyes +=  ( mFocus * Distance);
        }

        void MoveUpward( float Distance )
        {
        	mEyes += (mUp*Distance);
        }

        void StrafeRight ( float Distance )
        {
        	mEyes  +=    ( (mEyes - mFocus)^mUp ) *Distance;
        }


        void SetMouseInfo (int x, int y)
        {
        	mousePosition.Set(x,y);
        }

        void lockMouse(bool value)
        {
          if(value)
          {
            mouseLockedPosition = mousePosition;
          }

          mouseLocked = value;
        }

        Matrix4x4 ViewMatrix()
        {

            mViewMatrix = mOrientation.To4x4Matrix();

            xAxis.Set(mViewMatrix[0][0], mViewMatrix[0][1], mViewMatrix[0][2]);
            yAxis.Set(mViewMatrix[1][0], mViewMatrix[1][1], mViewMatrix[1][2]);
            zAxis.Set(mViewMatrix[2][0], mViewMatrix[2][1], mViewMatrix[2][2]);

            mFocus = -zAxis;

            mViewMatrix[0][3] = -(xAxis * mEyes);
            mViewMatrix[1][3] = -(yAxis * mEyes);
            mViewMatrix[2][3] = -(zAxis * mEyes);
        	//LookAt();
            return mViewMatrix;//ViewMatrixNormal();

                // Get the inverse of the arcball's rotation matrix
        		//Celer::Quaternion<float> cameraRotation = ~mTrackball.orientation();

                // Transform vectors based on camera's rotation matrix
//        		mUp = mOrientation.Rotate(Vector3::UNIT_Y);
//
//        		mEyes = mOrientation.Rotate(Vector3::UNIT_Z);
//
//              	mEyes =  (mEyes * mZoomRadius) - mPosition;

                // Update the eye point based on a radius away from the lookAt position
               // mEyes = cameraRotation.Rotate(mEyes);


        }

        void RotateView(float angle, float x, float y, float z)
        {
          Vector3 newView,
                  vView = mFocus;

          float cosTheta = std::cos(angle),
                sinTheta = std::sin(angle);

          vView -= mEyes;

          // Find the new x position for the new rotated point
          newView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
          newView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
          newView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

          // Find the new y position for the new rotated point
          newView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
          newView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
          newView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

          // Find the new z position for the new rotated point
          newView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
          newView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
          newView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

          // Now we just add the newly rotated vector to our position to set
          // our new rotated view of our camera.
          mFocus  = mEyes;
          mFocus += newView;
        }


        void SetViewByMouse()
        {
          float          pitch        = 0.0f,
						 heading        = 0.0f;

          if((mousePosition == mouseLockedPosition) || !mouseLocked)
          {
        	  return;
          }


          pitch    = float(mouseLockedPosition.x - mousePosition.x)*Math::kDeg2Rad*0.2;
          heading  = float(mouseLockedPosition.y - mousePosition.y)*Math::kDeg2Rad*0.2;


//          Vector3 vAxis     = mFocus;
//                  vAxis     = mFocus - mEyes;
//                  vAxis     = vAxis ^ mUp;
//         vAxis.Normalize();


          Rotate(-heading,-pitch,0.0f);
//          RotateView(heading, vAxis.x, vAxis.y, vAxis.z);
//          RotateView(pitch, 0, 1, 0);



          if(!mouseLocked)
          {
            mouseLockedPosition = mousePosition;
          }

        }

        Matrix4x4 ViewMatrixNormal()
        {

        	return Matrix4x4::MakeViewMatrix(mEyes, mFocus, mUp);

        }

        Matrix4x4 ViewMatrix( Vector3& pEyes, Vector3& pFocus, Vector3& pUp )
        {
        	return Matrix4x4::MakeViewMatrix(pEyes, pFocus, pUp);
        }


        Matrix4x4 PespectiveProjectionMatrix()
        {
                return mPespectiveProjectionMatrix;
        }

        Matrix4x4 OrthographicProjectionMatrix()
        {
                return mOrthographicProjectionMatrix;
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
                rotateFirstPerson(headingDegrees, pitchDegrees);
                break;

            case FLIGHT:

                break;
            }


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
                mOrientation = mOrientation * rot;
            }

            // Rotate camera about its local x axis.
            // Note the order the quaternions are multiplied. That is important!
            if (pitchDegrees != 0.0f)
            {
                rot.FromAxisAngle(Vector3::UNIT_X, pitchDegrees);
                mOrientation = rot * mOrientation;
            }
             mOrientation.Normalize();
        }


        void LookAt()
        {

            zAxis = mEyes - mFocus;
            zAxis.Normalize();

            xAxis = (mUp ^ zAxis);
            xAxis.Normalize();

            yAxis = (zAxis ^ xAxis);
            yAxis.Normalize();

            mViewMatrix[0][0] = xAxis.x;
            mViewMatrix[0][1] = xAxis.y;
            mViewMatrix[0][2] = xAxis.z;
            mViewMatrix[0][3] = -(xAxis * mEyes);

            mViewMatrix[1][0] = yAxis.x;
            mViewMatrix[1][1] = yAxis.y;
            mViewMatrix[1][2] = yAxis.z;
            mViewMatrix[1][3] = -(yAxis * mEyes);

            mViewMatrix[2][0] = zAxis.x;
            mViewMatrix[2][1] = zAxis.y;
            mViewMatrix[2][2] = zAxis.z;
            mViewMatrix[2][3] = -(zAxis * mEyes);

            // Extract the pitch angle from the view matrix.
            mAccumPitchDegrees = Math::kRad2Deg * (std::asin(mViewMatrix[2][1]));

            mOrientation.FromRotationMatrix(mViewMatrix);
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
            mEyes = mInitalPosition;
            mTrackball.Reset();
        }


    private:

    	Vector3 mInitalPosition;

    	Quaternion mOrientation;
    	float mAccumPitchDegrees;

        float pitchDegrees;
        float headingDegrees;
        float rollDegrees;


        Vector2  mouseLockedPosition;
        Vector2  mousePosition;
        bool     mouseLocked;

    	CameraBehavior mBehavior;

    	Vector3 mFocus;    //Where the camera looked at
    	Vector3 mEyes;	   //Where the camera is. Camera position
    	Vector3 mUp;	   //Self Documentation

    	Vector3 xAxis;
    	Vector3 yAxis;
    	Vector3 zAxis;

    	float mWidth;
    	float mHeight;

    	float mZoomRadius;
    	float mMinRadius;
    	float mMaxRadius;

    	Trackball mTrackball;

    	Matrix4x4 mViewMatrix;

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

}/* Celer :: NAMESPACE */

#endif /*CAMERA_HPP_*/
