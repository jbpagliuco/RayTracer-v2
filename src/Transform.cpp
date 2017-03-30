#include <Transform.h>

#include <sstream>

namespace RT
{
	Transform::Transform()
	{
		position = VML::VectorZero();
		inv = VML::MatrixIdentity();
	}

	Transform::Transform(const VML::VECTOR3F& position, const VML::VECTOR3F& rotation, const VML::VECTOR3F& scale)
	{
		this->position = VML::Vector(position.x, position.y, position.z, 1.0f);
		this->scale = VML::Vector(scale.x, scale.y, scale.z, 1.0f);

		calculateMatrices(VML::Vector(position), rotation, VML::Vector(scale));
	}

	Transform::~Transform()
	{

	}

	void Transform::calculateMatrices(const VML::Vector& position, const VML::VECTOR3F& rotation, const VML::Vector scale)
	{
		VML::Matrix t = VML::MatrixTranslation(position);
		VML::Matrix r = VML::MatrixRotationEuler(rotation.x, rotation.y, rotation.z);
		VML::Matrix s = VML::MatrixScaling(scale);
		inv = t * r * s;
		inv.invert(nullptr);

		invT = VML::Matrix(inv);
		invT.transpose();
	}


	Ray Transform::transformRay(const Ray& ray)const
	{
		VML::Vector o = inv * ray.origin();
		VML::Vector d = inv * ray.direction();
		return Ray(o, d, false);
	}

	VML::Vector Transform::transformNormal(const VML::Vector& normal)const
	{
		VML::Vector tn = (invT * normal).v3Normalize();
		return VML::Vector(tn.getX(), tn.getY(), tn.getZ(), 0.0f);
	}

	VML::Vector Transform::transformPoint(const VML::Vector& point)const
	{
		VML::Vector p(point.getX(), point.getY(), point.getZ(), 1.0f);
		VML::Vector tp = (inv * p);
		return VML::Vector(tp.getX(), tp.getY(), tp.getZ(), 1.0f);
	}




	Transform LoadTransform(const std::string& params)
	{
		std::stringstream ss(params);

		VML::VECTOR3F position, rotation, scale;
		ss >> position.x >> position.y >> position.z >>
			rotation.x >> rotation.y >> rotation.z >>
			scale.x >> scale.y >> scale.z;

		rotation.x = rotation.x * PI / 180.0f;
		rotation.y = rotation.y * PI / 180.0f;
		rotation.z = rotation.z * PI / 180.0f;

		return Transform(position, rotation, scale);
	}
}