#pragma once

#include "GlobalHeaders.h"

#define RAD_TO_DEG(rad) (float)((rad)*(180)/(M_PI))
#define DEG_TO_RAD(deg) (float)((deg)*(M_PI)/(180))

class LIFEUNIVERSALIS_EXPORT Transform
{
public:
	//! Default c'tor. Sets local position to (0, 0, 0), local Euler angles to (0, 0, 0) and 
	//! local scale to (1, 1, 1).
	Transform();

	//! Sets local position to (0, 0, 0), local Euler angles to (0, 0, 0) and 
	//! local scale to (1, 1, 1).
	void reset();

	//! Sets world rotation and world position of the transform.
	//! \param forward - Z versor in world coordinates.
	//! \param left - X versor in world coordinates.
	//! \param pos - World position.
	void fromForwardLeftPosition(const Vector3 &forward, const Vector3 &left, 
		const Vector3 &pos);

	//! Makes 'this' transform to be child of 'parent' transform.
	void setParent(Transform *parent);

	//! Sets local position of the transform to 'pos'.
	void setLocalPosition(const Vector3 &pos);

	//! \return Local position of the transform.
	const Vector3& getLocalPosition() const;

	//! Sets world position of the transform to 'pos'.
	void setWorldPosition(const Vector3 &pos);

	//! \return World position of the transform.
	const Vector3 getWorldPosition() const;

	//! Moves the transform by 'translationVec'.
	void translate(const Vector3 &translationVec);

	//! \return Quaternion describing local rotation of the transform.
	const Quaternion getLocalQuaternion() const;

	//! Sets local rotation of the transform to 'quaternion'.
	//! \param quaternion - normalized quaternion defining rotation.
	void setLocalQuaternion(const Quaternion &quaternion);

	//! \return Quaternion describing world rotation of the transform.
	const Quaternion getWorldQuaternion() const;

	//! Sets world rotation of the transform to 'quaternion'.
	//! \param quaternion - normalized quaternion defining rotation.
	void setWorldQuaternion(const Quaternion &quaternion);

	//! \return Euler angles in radians defining local rotation of the transform.
	const Vector3 getLocalEulerAngles() const;

	//! Sets local rotation of the transform according to 'eulerAngles'.
	//! \param eulerAngles - Vector containing euler angles around x, y and z in radians.
	void setLocalEulerAngles(const Vector3 &eulerAngles);

	//! \return Euler angles in radians defining world rotation of the transform.
	const Vector3 getWorldEulerAngles() const;

	//! Sets world rotation of the transform according to 'eulerAngles'.
	//! \param eulerAngles - Vector containing euler angles around x, y and z in radians.
	void setWorldEulerAngles(const Vector3 &eulerAngles);

	//! Rotates the transform by 'eulerAngles'. Note that the rotation order is ZXY and the 
	//! rotation axes XYZ are taken from the static frame, i.e. the one before rotation.
	void rotate(const Vector3 &eulerAngles);

	//! Rotates the transform given axis and angle.
	//! \param axis - Normalized vector starting at local coordinate system origin.
	//! \param angle - Rotation angle in radians.
	void rotate(const Vector3 &axis, float angle);

	//! \return Local scale of the transform.
	const Vector3 getLocalScale() const;

	//! Sets local scale of the transform to 'scale'.
	void setLocalScale(const Vector3 &scale);

	//! \return Z versor of the transform in world coordinates.
	const Vector3 getForwardVersor() const;

	//! \return X versor of the transform in world coordinates.
	const Vector3 getLeftVersor() const;

	//! \return Y versor of the transform in world coordinates.
	const Vector3 getUpVersor() const;

	//! \return Matrix that transforms a point from world space to local space.
	const Matrix4& getWorldToLocalMatrix() const;

	//! \return Matrix that transforms a point from local space to world space.
	const Matrix4& getLocalToWorldMatrix() const;

private:
	void _computeTransformationMatrices() const;

	const Vector3 _getParentWorldPosition() const;

	const Matrix4 _getParentWorldToLocalMatrix() const;

	const Quaternion _convertEulerAnglesToQuaternion(const Vector3 &eulerAngles);

	// Local position of the transform.
	Vector3 _localPosition;

	// Quaternion to store the local rotation of the transform.
	Quaternion _localQuaternion;

	// Local scale of the transform.
	Vector3 _localScale;

	//! Flag indicating whether the cached matrices need to be recomputed.
	mutable bool _shouldComputeMatrices;

	//! Matrix that transforms a point from world space to local space.
	mutable Matrix4 _worldToLocalMatrix;

	//! Matrix that transforms a point from local space to world space.
	mutable Matrix4 _localToWorldMatrix;

	//! Parent transform of this transform.
	Transform *_parent;
};
