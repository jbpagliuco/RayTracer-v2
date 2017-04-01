#include <Geometry.h>

namespace RT
{
	Ray::Ray()
	{
		o = VML::Vector(0.0f, 0.0f, 0.0f, 1.0f);
		d = VML::Vector(0.0f, 0.0f, 1.0f, 0.0f);
	}

	Ray::Ray(const VML::VECTOR3F& origin, const VML::VECTOR3F& direction)
	{
		o = VML::Vector(origin.x, origin.y, origin.z, 1.0f);
		d = VML::Vector(direction.x, direction.y, direction.z, 0.0f).v3Normalize();
	}

	Ray::Ray(const VML::Vector& origin, const VML::Vector& direction, F32 epsilon)
	{
		d = VML::Vector(direction.getX(), direction.getY(), direction.getZ(), 0.0f).v3Normalize();
		o = origin + (d * epsilon);
		o = VML::Vector(o.getX(), o.getY(), o.getZ(), 1.0f);
	}

	Ray::Ray(const VML::Vector& origin, const VML::Vector& direction, bool bNormalize)
	{
		d = VML::Vector(direction.getX(), direction.getY(), direction.getZ(), 0.0f);
		if (bNormalize)
			d.v3Normalize();
		o = VML::Vector(origin.getX(), origin.getY(), origin.getZ(), 1.0f);
	}

	VML::Vector Ray::getPointAlongRay(F32 t)const
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