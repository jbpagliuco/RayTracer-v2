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

	bool Triangle::findBarycentricCoords(D64& beta, D64& gamma, D64& t, VML::VECTOR3F points[3], const Ray& ray)const
	{
		D64 a = points[0].x - points[1].x, b = points[0].x - points[2].x, c = ray.direction().getX(), d = points[0].x - ray.origin().getX();
		D64 e = points[0].y - points[1].y, f = points[0].y - points[2].y, g = ray.direction().getY(), h = points[0].y - ray.origin().getY();
		D64 i = points[0].z - points[1].z, j = points[0].z - points[2].z, k = ray.direction().getZ(), l = points[0].z - ray.origin().getZ();

		D64 m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		D64 q = g * i - e * k, s = e * j - f * i;

		D64 inv_denom = 1.0 / (a * m + b * q + c * s);

		D64 e1 = d * m - b * n - c * p;
		beta = e1 * inv_denom;

		if (beta < 0.0)
			return false;

		D64 r = e * l - h * i;
		D64 e2 = a * n + d * q + c * r;
		gamma = e2 * inv_denom;

		if (gamma < 0.0)
			return false;

		if (beta + gamma > 1.0)
			return false;

		D64 e3 = a * p - b * r + d * s;
		t = e3 * inv_denom;

		if (t < VML::FLOAT_EPSILON)
			return false;

		return true;
	}

	bool Triangle::findHitPoint(RayIntersection& outHitInfo, const Ray& ray)const
	{
		D64 beta, gamma, t;
		VML::VECTOR3F points[3] = { p1, p2, p3 };
		bool bHit = findBarycentricCoords(beta, gamma, t, points, ray);

		outHitInfo.t = (F32)t;
		outHitInfo.normal = normal;
		outHitInfo.worldCoords = ray.getPointAlongRay((F32)t);

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