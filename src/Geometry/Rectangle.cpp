#include <Primitives.h>

namespace RT
{
	Rectangle::Rectangle(): p0(-1.0f, 0.0f, -1.0f, 1.0f), 
		a(2.0f, 0.0f, 0.0f, 0.0f), b(0.0f, 0.0f, 2.0f, 0.0f),
		normal(0.0f, 1.0f, 0.0f, 0.0f), invArea(0.25f)
	{
	}

	bool Rectangle::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		return findHitPoint(outHitInfo, ray);
	}

	bool Rectangle::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection outHitInfo;
		bool bHit = findHitPoint(outHitInfo, ray);
		tmin = outHitInfo.t;
		return bHit;
	}

	bool Rectangle::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		F32 dDOTn = ray.direction().v3Dot(normal);
		if (VML::FEquals(dDOTn, 0.0f))
			return false;

		VML::Vector;
		F32 t = (p0 - ray.origin()).v3Dot(normal) / dDOTn;

		if (t <= VML::FLOAT_EPSILON)
			return false;

		VML::Vector p = ray.getPointAlongRay(t);
		VML::Vector d = p - p0;

		F32 dDOTa = d.v3Dot(a);
		if (dDOTa < 0.0f || dDOTa > a.v3LengthSq())
			return false;

		F32 dDOTb = d.v3Dot(b);
		if (dDOTb < 0.0f || dDOTb > b.v3LengthSq())
			return false;

		outHitInfo.t = t;
		outHitInfo.normal = normal;
		outHitInfo.worldCoords = p;

		return true;
	}

	BoundingBox Rectangle::getBoundingBox()const
	{
		VML::VECTOR3F min(-1.0f, -1.0f, -VML::FLOAT_EPSILON);
		VML::VECTOR3F max(1.0f, 1.0f, VML::FLOAT_EPSILON);

		return BoundingBox(min, max);
	}




	PGeometry LoadRectangle(std::stringstream& ss, World& world)
	{
		return AllocateAligned16(Rectangle());
	}
}