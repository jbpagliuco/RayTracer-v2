#include <Geometry.h>

namespace RT
{
	Ray::Ray()
	{
		this->o = VML::VectorZero();
		this->d = VML::Vector(0.0f, 0.0f, 1.0f, 0.0f);
	}

	Ray::Ray(const VML::VECTOR3F& origin, const VML::VECTOR3F& direction)
	{
		this->o = VML::Vector(origin);
		this->d = VML::Vector(direction.x, direction.y, direction.z, 0.0f).v3Normalize();
	}

	Ray::Ray(const VML::Vector& origin, const VML::Vector& direction, F32 epsilon)
	{
		this->d = VML::Vector(direction).v3Normalize();
		this->o += origin + (this->d * epsilon);
	}

	VML::Vector Ray::GetPointAlongRay(F32 t)const
	{
		VML::Vector v = o + (d * t);
		return v;
	}


	VML::Vector Ray::origin()const
	{
		return o;
	}

	VML::Vector Ray::direction()const
	{
		return d;
	}
}