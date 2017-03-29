#include <Primitives.h>

namespace RT
{
	Disk::Disk(F32 radius) : radiusSq(radius*radius) {}

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
		const VML::Vector normal(0.0f, 1.0f, 0.0f, 0.0f);
		F32 dn = ray.direction().v3Dot(normal);
		if (VML::FEquals(dn, 0.0f))
			return false;

		F32 t = ray.origin().negate().v3Dot(normal) / dn;
		if (t <= VML::FLOAT_EPSILON)
			return false;

		VML::Vector p = ray.GetPointAlongRay(t);

		F32 distSqr = p.v3LengthSq();
		if (distSqr < radiusSq)
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
		F32 r = sqrt(radiusSq);
		VML::VECTOR3F min(-r, -r, -r);
		VML::VECTOR3F max(r, r, r);
		return BoundingBox(min, max);
	}




	PGeometry LoadDisk(std::stringstream& ss, World& world)
	{
		F32 radius;
		ss >> radius;

		return AllocateAligned16(Disk(radius));
	}
}