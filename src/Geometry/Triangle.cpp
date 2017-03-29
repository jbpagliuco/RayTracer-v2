#include <Primitives.h>

#include <algorithm>

namespace RT
{
	Triangle::Triangle(VML::VECTOR3F p1, VML::VECTOR3F p2, VML::VECTOR3F p3)
	{
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;

		VML::Vector a(p1);
		VML::Vector b(p2);
		VML::Vector c(p3);

		normal = ((b - a).v3Cross((c - a))).v3Normalize();
	}

	bool Triangle::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		return findHitPoint(outHitInfo, ray);
	}

	bool Triangle::shadowHits(F32& tmin, const Ray& ray)const
	{
		RayIntersection outHitInfo;
		bool bHit = findHitPoint(outHitInfo, ray);
		tmin = outHitInfo.t;
		return bHit;
	}

	bool Triangle::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		F32 a = p1.x - p2.x, b = p1.x - p3.x, c = ray.direction().getX(), d = p1.x - ray.origin().getX();
		F32 e = p1.y - p2.y, f = p1.y - p3.y, g = ray.direction().getY(), h = p1.y - ray.origin().getY();
		F32 i = p1.z - p2.z, j = p1.z - p3.z, k = ray.direction().getZ(), l = p1.z - ray.origin().getZ();

		F32 m = f * k - g * i;
		F32 n = h * k - g * l;
		F32 p = f * l - h * j;

		F32 q = g * i - e * k;
		F32 s = e * j - f * i;

		F32 invDenom = 1.0f / (a * m + b * q + c * s);

		F32 e1 = d * m - b * n - c * p;
		F32 beta = e1 * invDenom;

		if (beta < 0.0f)
			return false;

		F32 r = e * l - h * i;
		F32 e2 = a * n + d * q + c * r;
		F32 gamma = e2 * invDenom;

		if (gamma < 0.0f)
			return false;

		if (beta + gamma > 1.0f)
			return false;

		F32 e3 = a * p - b * r + d * s;
		F32 t = e3 * invDenom;

		if (t < VML::FLOAT_EPSILON)
			return false;

		outHitInfo.t = t;
		outHitInfo.normal = normal;
		outHitInfo.worldCoords = ray.GetPointAlongRay(t);

		return true;
	}

	BoundingBox Triangle::getBoundingBox()const
	{
		VML::VECTOR3F min(
			std::min(p1.x, std::min(p2.x, p3.x)),
			std::min(p1.y, std::min(p2.y, p3.y)),
			std::min(p1.z, std::min(p2.z, p3.z)));
		
		VML::VECTOR3F max(
			std::max(p1.x, std::max(p2.x, p3.x)),
			std::max(p1.y, std::max(p2.y, p3.y)),
			std::max(p1.z, std::max(p2.z, p3.z)));

		return BoundingBox(min, max);
	}


	PGeometry LoadTriangle(std::stringstream& ss, World& world)
	{
		VML::VECTOR3F p1, p2, p3;

		ss >> p1.x >> p1.y >> p1.z >>
			p2.x >> p2.y >> p2.z >>
			p3.x >> p3.y >> p3.z;

		return AllocateAligned16(Triangle(p1, p2, p3));
	}
}