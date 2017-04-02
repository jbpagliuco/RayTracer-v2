#include <Primitives.h>

namespace RT
{
	Sphere::Sphere() : radius(1.0f) {}

	Sphere::Sphere(F32 radius) : radius(radius) {}

	bool Sphere::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		return findHitPoint(outHitInfo, ray);
	}

	bool Sphere::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection out;
		bool bHit = findHitPoint(out, ray);
		tmin = out.t;
		return bHit;
	}

	BoundingBox Sphere::getBoundingBox()const
	{
		VML::VECTOR3F min(-radius, -radius, -radius);
		VML::VECTOR3F max(radius, radius, radius);
		return BoundingBox(min, max);
	}

	bool Sphere::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		VML::Vector o = ray.origin();
		VML::Vector d = ray.direction();

		F32 a = d.v3Dot(d);
		F32 b = (o * 2.0f).v3Dot(d);
		F32 c = (o.v3Dot(o)) - (radius * radius);

		F32 disc = (b * b) - (4 * a * c);

		if (disc < 0)
			return false;
		else
		{
			F32 e = sqrt(disc);
			F32 den = 2.0f * a;

			F32 t = (-b - e) / den;
			if (t > F32_EPS)
			{
				outHitInfo.t = t;
				outHitInfo.worldCoords = ray.getPointAlongRay(t);
				VML::Vector normal = outHitInfo.worldCoords.v3Normalize();
				outHitInfo.normal = VML::Vector(normal.getX(), normal.getY(), normal.getZ(), 0.0f);

				return true;
			}

			t = (-b + e) / den;
			if (t > F32_EPS)
			{
				outHitInfo.t = t;
				outHitInfo.worldCoords = ray.getPointAlongRay(t);
				VML::Vector normal = outHitInfo.worldCoords.v3Normalize();
				outHitInfo.normal = VML::Vector(normal.getX(), normal.getY(), normal.getZ(), 0.0f);
				return true;
			}
		}

		return false;
	}



	PGeometry LoadSphere(std::stringstream& ss, World& world)
	{
		F32 radius;
		ss >> radius;

		return AllocateAligned16(Sphere(radius));
	}
}