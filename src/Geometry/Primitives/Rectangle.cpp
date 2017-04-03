#include <Primitives.h>

namespace RT
{
	Rectangle::Rectangle(): p0(0.0f, 0.0f, 0.0f, 1.0f), 
		a(1.0f, 0.0f, 0.0f, 0.0f), b(0.0f, 0.0f, 1.0f, 0.0f),
		normal(0.0f, 1.0f, 0.0f, 0.0f)
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
		VML::VECTOR3F min = p0.asVector3();
		VML::VECTOR3F max = (p0 + a + b).asVector3();

		return BoundingBox(min, max);
	}
	
	F32 Rectangle::pdf(const ElementIntersection& ei, const Transform& transform)const
	{
		const VML::Vector ta = transform.transformVector(a);
		const VML::Vector tb = transform.transformVector(b);

		return 1.0f / (ta.v3Length() * tb.v3Length());
	}

	VML::Vector Rectangle::sample()
	{
		VML::VECTOR2F s = sampler.sampleUnitSquare();
		VML::Vector v = (p0 + (a * s.x) - (b * s.y));
		return VML::Vector(v.getX(), v.getY(), v.getZ(), 1.0f);
	}

	VML::Vector Rectangle::getNormalAtPoint(const VML::Vector& point)const
	{
		return normal;
	}




	PGeometry LoadRectangle(std::stringstream& ss, World& world)
	{
		return AllocateAligned16(Rectangle());
	}
}