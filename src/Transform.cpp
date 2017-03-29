#include <Transform.h>

#include <sstream>

namespace RT
{
	Transform::Transform() : position(VML::VectorZero())
	{

	}

	Transform::Transform(const VML::VECTOR3F& position) : position(position)
	{

	}

	Transform::Transform(const VML::Vector& position) : position(position)
	{

	}

	Transform::~Transform()
	{

	}


	Ray Transform::TransformRay(const Ray& ray)const
	{
		return Ray(ray.origin() - position, ray.direction());
	}




	Transform LoadTransform(const std::string& params)
	{
		std::stringstream ss(params);

		VML::VECTOR3F position;
		ss >> position.x >> position.y >> position.z;

		return Transform(position);
	}
}