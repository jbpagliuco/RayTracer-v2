#include <Transform.h>

#include <sstream>

namespace RT
{
	Transform::Transform()
	{
		position = VML::VectorZero();
		inv = VML::MatrixIdentity();
	}

	Transform::Transform(const VML::VECTOR3F& position, const VML::VECTOR3F& scale)
	{
		this->position = VML::Vector(position.x, position.y, position.z, 1.0f);

		calculateMatrices(this->position, VML::Vector(scale));
	}

	Transform::Transform(const VML::Vector& position) : position(position)
	{
		calculateMatrices(position, VML::Vector(1.0f, 1.0f, 1.0f, 0.0f));
	}

	Transform::~Transform()
	{

	}

	void Transform::calculateMatrices(const VML::Vector& position, const VML::Vector scale)
	{
		inv = VML::MatrixScaling(scale) * VML::MatrixTranslation(position);
		inv.invert(nullptr);

		invT = VML::Matrix(inv);
		invT.transpose();
	}


	Ray Transform::transformRay(const Ray& ray)const
	{
		VML::Vector o = inv * ray.origin();
		VML::Vector d = inv * ray.direction();
		return Ray(o, d);
	}

	VML::Vector Transform::transformNormal(const VML::Vector& normal)const
	{
		VML::Vector tn = (invT * normal).v3Normalize();
		return VML::Vector(tn.getX(), tn.getY(), tn.getZ(), 0.0f);
	}




	Transform LoadTransform(const std::string& params)
	{
		std::stringstream ss(params);

		VML::VECTOR3F position, scale;
		ss >> position.x >> position.y >> position.z >>
			scale.x >> scale.y >> scale.z;

		return Transform(position, scale);
	}
}