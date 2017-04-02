#include <Primitives.h>

namespace RT
{
	Disk::Disk() : normal(0.0f, 1.0f, 0.0f, 0.0f) {}

	bool Disk::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		return findHitPoint(outHitInfo, ray);
	}

	bool Disk::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection outHitInfo;
		bool bHit = findHitPoint(outHitInfo, ray);
		tmin = outHitInfo.t;
		return bHit;
	}

	bool Disk::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		F32 dn = ray.direction().v3Dot(normal);
		if (VML::FEquals(dn, 0.0f))
			return false;

		F32 t = ray.origin().negate().v3Dot(normal) / dn;
		if (t <= VML::FLOAT_EPSILON)
			return false;

		VML::Vector p = ray.getPointAlongRay(t);

		F32 distSqr = p.v3LengthSq();
		if (distSqr < 1.0f)
		{
			RayIntersection r;
			r.t = t;
			r.normal = normal;
			r.worldCoords = p;

			outHitInfo = r;

			return true;
		}

		return false;
	}

	BoundingBox Disk::getBoundingBox()const
	{
		F32 r = 1.0f;
		VML::VECTOR3F min(-r, -r, -r);
		VML::VECTOR3F max(r, r, r);
		return BoundingBox(min, max);
	}




	PGeometry LoadDisk(std::stringstream& ss, World& world)
	{
		return AllocateAligned16(Disk());
	}
}