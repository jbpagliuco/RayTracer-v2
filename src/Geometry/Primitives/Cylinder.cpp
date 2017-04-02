#include <Primitives.h>

namespace RT
{
	Cylinder::Cylinder() {}

	bool Cylinder::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		return findHitPoint(outHitInfo, ray);
	}

	bool Cylinder::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection out;
		bool bHit = findHitPoint(out, ray);
		tmin = out.t;
		return bHit;
	}

	BoundingBox Cylinder::getBoundingBox()const
	{
		VML::VECTOR3F min(-1.0f, -1.0f, -1.0f);
		VML::VECTOR3F max(1.0f, 1.0f, 1.0f);
		return BoundingBox(min, max);
	}

	bool Cylinder::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		VML::Vector o(ray.origin().getX(), 0.0f, ray.origin().getZ(), 1.0f);
		VML::Vector d(ray.direction().getX(), 0.0f, ray.direction().getZ(), 0.0f);

		F32 a = d.v3Dot(d);
		F32 b = o.v3Dot(d) * 2.0f;
		F32 c = (o.v3Dot(o)) - 1; // -(radius * radius); radius = 1

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
				outHitInfo.normal = VML::Vector(outHitInfo.worldCoords.getX(), 0.0f, outHitInfo.worldCoords.getZ(), 0.0f);

				return true;
			}

			t = (-b + e) / den;
			if (t > F32_EPS)
			{
				outHitInfo.t = t;
				outHitInfo.worldCoords = ray.getPointAlongRay(t);
				outHitInfo.normal = VML::Vector(outHitInfo.worldCoords.getX(), 0.0f, outHitInfo.worldCoords.getZ(), 0.0f);
				return true;
			}
		}

		return false;
	}



	PGeometry LoadCylinder(std::stringstream& ss, World& world)
	{
		return AllocateAligned16(Cylinder());
	}
}