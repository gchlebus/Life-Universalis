#include "Transform.h"

Transform::Transform()
	: _shouldComputeMatrices(true)
	, _parent(nullptr)
{
	reset();
}

void Transform::reset()
{
	_shouldComputeMatrices = true;
	_localPosition.setZero();
	_localQuaternion.setIdentity();
	_localScale.setOnes();
}

void Transform::fromForwardLeftPosition(const Vector3 &forward, const Vector3 &left, 
	const Vector3 &pos)
{
	_shouldComputeMatrices = true;

	setWorldPosition(pos);

	Matrix3 m;
	m.col(0) = left.normalized();
	m.col(1) = forward.cross(left).normalized();
	m.col(2) = left.cross(m.col(1)).normalized();
	Quaternion q(m);
	setWorldQuaternion(q.normalized());
}

void Transform::setParent(Transform *parent)
{
	_shouldComputeMatrices = true;
	_parent = parent;
}

void Transform::setLocalPosition(const Vector3 &pos)
{
	_shouldComputeMatrices = true;
	_localPosition = pos;
}

const Vector3& Transform::getLocalPosition() const
{
	return _localPosition;
}

void Transform::setWorldPosition(const Vector3 &pos)
{
	_shouldComputeMatrices = true;
	_localPosition = pos - _getParentWorldPosition();
}

const Vector3 Transform::getWorldPosition() const
{
	return Eigen::Affine3f(_getParentWorldToLocalMatrix()) * _localPosition;
}

void Transform::translate(const Vector3 &translationVec)
{
	_shouldComputeMatrices = true;
	_localPosition += translationVec;
}

const Quaternion Transform::getLocalQuaternion() const
{
	return _localQuaternion;
}

void Transform::setLocalQuaternion(const Quaternion &quaternion)
{
	_shouldComputeMatrices = true;
	_localQuaternion = quaternion;
}

const Quaternion Transform::getWorldQuaternion() const
{
	Eigen::Affine3f t(_getParentWorldToLocalMatrix());
	t *= _localQuaternion;
	return Quaternion(t.rotation());
}

void Transform::setWorldQuaternion(const Quaternion &quaternion)
{
	_shouldComputeMatrices = true;
	Eigen::Affine3f t(_getParentWorldToLocalMatrix());
	_localQuaternion = t.rotation().inverse() * quaternion;
}

const Vector3 Transform::getLocalEulerAngles() const
{
	Vector3 anglesZXY = _localQuaternion.toRotationMatrix().eulerAngles(2, 0, 1);
	return Vector3(anglesZXY[1], anglesZXY[2], anglesZXY[0]);
}

void Transform::setLocalEulerAngles(const Vector3 &eulerAngles)
{
	_shouldComputeMatrices = true;
	_localQuaternion = _convertEulerAnglesToQuaternion(eulerAngles);
}

const Vector3 Transform::getWorldEulerAngles() const
{
	Eigen::Affine3f t(_getParentWorldToLocalMatrix());
	t *= _localQuaternion;
	Vector3 anglesZXY = t.rotation().eulerAngles(2, 0, 1);
	return Vector3(anglesZXY[1], anglesZXY[2], anglesZXY[0]);
}

void Transform::setWorldEulerAngles(const Vector3 &eulerAngles)
{
	_shouldComputeMatrices = true;
	Quaternion q = _convertEulerAnglesToQuaternion(eulerAngles);
	Eigen::Affine3f t(_getParentWorldToLocalMatrix());
	_localQuaternion = t.rotation().inverse() * q;
}

void Transform::rotate(const Vector3 &eulerAngles)
{
	_shouldComputeMatrices = true;

	Eigen::AngleAxisf rotZ(eulerAngles.z(), getForwardVersor());
	Eigen::AngleAxisf rotX (eulerAngles.x(), getLeftVersor());
	Eigen::AngleAxisf rotY(eulerAngles.y(), getUpVersor());

	_localQuaternion = rotZ * rotX * rotY * _localQuaternion;
}

void Transform::rotate(const Vector3 &axis, float angle)
{
	_shouldComputeMatrices = true;
	Eigen::AngleAxisf rot(angle, axis);
	_localQuaternion = rot * _localQuaternion;
}

const Vector3 Transform::getLocalScale() const
{
	return _localScale;
}

void Transform::setLocalScale(const Vector3 &scale)
{
	_shouldComputeMatrices = true;
	_localScale = scale;
}

const Vector3 Transform::getForwardVersor() const
{
	return getWorldQuaternion().toRotationMatrix() * Vector3::UnitZ();
}

const Vector3 Transform::getLeftVersor() const
{
	return getWorldQuaternion().toRotationMatrix() * Vector3::UnitX();
}

const Vector3 Transform::getUpVersor() const
{
	return getWorldQuaternion().toRotationMatrix() * Vector3::UnitY();
}

const Matrix4& Transform::getWorldToLocalMatrix() const
{
	if (_shouldComputeMatrices)
	{
		_computeTransformationMatrices();
	}

	return _worldToLocalMatrix;
}

const Matrix4& Transform::getLocalToWorldMatrix() const
{
	if (_shouldComputeMatrices)
	{
		_computeTransformationMatrices();
	}

	return _localToWorldMatrix;
}

void Transform::_computeTransformationMatrices() const
{
	_shouldComputeMatrices = false;

	Eigen::Affine3f t;
	t.fromPositionOrientationScale(_localPosition, _localQuaternion, _localScale);
	_worldToLocalMatrix = _getParentWorldToLocalMatrix() * t.matrix();
	_localToWorldMatrix = _worldToLocalMatrix.inverse();
}

const Vector3 Transform::_getParentWorldPosition() const
{
	Eigen::Affine3f t(_getParentWorldToLocalMatrix());
	return t.translation();
}

const Matrix4 Transform::_getParentWorldToLocalMatrix() const
{
	Matrix4 m(Matrix4::Identity());

	if (_parent)
	{
		m = _parent->getWorldToLocalMatrix();
	}

	return m;
}

const Quaternion Transform::_convertEulerAnglesToQuaternion(const Vector3 &eulerAngles)
{
	Eigen::AngleAxisf rotZ(eulerAngles.z(), Vector3::UnitZ());
	Eigen::AngleAxisf rotX (eulerAngles.x(), Vector3::UnitX());
	Eigen::AngleAxisf rotY(eulerAngles.y(), Vector3::UnitY());

	return rotZ * rotX * rotY;
}
