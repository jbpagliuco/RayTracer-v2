#include <Primitives.h>

namespace RT
{
	Plane::Plane() {}

	bool Plane::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		return findHitPoint(outHitInfo, ray);
	}

	bool Plane::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection outHitInfo;
		bool bHit = findHitPoint(outHitInfo, ray);
		tmin = outHitInfo.t;
		return bHit;
	}

	bool Plane::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		const VML::Vector normal(0.0f, 1.0f, 0.0f, 0.0f);
		F32 dn = ray.direction().v3Dot(normal);
		F32 num = ray.origin().negate().v3Dot(normal);

		if (VML::FEquals(dn, 0.0f))
			return false;

		F32 t = num / dn;
		if (t >= VML::FLOAT_EPSILON)
		{
			outHitInfo.t = t;
			outHitInfo.worldCoords = ray.getPointAlongRay(t);
			outHitInfo.normal = normal;
			
			const F32 scale = 7.0f;
			VML::VECTOR2F uv(outHitInfo.worldCoords.getX() / scale, outHitInfo.worldCoords.getZ() / scale);
			outHitInfo.uv = VML::VECTOR2F(fabsf(uv.x - (I32)uv.x), fabsf(uv.y - (I32)uv.y));
			return true;
		}

		return false;
	}

	bool Plane::hasBounds()const
	{
		return false;
	}




	PGeometry LoadPlane(std::stringstream& ss, World& world)
	{
		return AllocateAligned16(Plane());
	}
}