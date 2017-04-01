#include <BoundingVolume.h>

#include <Geometry.h>
#include <algorithm>

namespace RT
{
	BoundingBox::BoundingBox()
	{

	}

	BoundingBox::BoundingBox(const VML::VECTOR3F& min, const VML::VECTOR3F& max, bool bAddEpsilon)
	{
		this->min = VML::VECTOR3F(std::min(min.x, max.x), std::min(min.y, max.y), std::min(min.z, max.z));
		this->max = VML::VECTOR3F(std::max(min.x, max.x), std::max(min.y, max.y), std::max(min.z, max.z));

		if (bAddEpsilon)
		{
			this->min.x -= F32_EPS;
			this->min.y -= F32_EPS;
			this->min.z -= F32_EPS;

			this->max.x += F32_EPS;
			this->max.y += F32_EPS;
			this->max.z += F32_EPS;
		}
	}

	BoundingBox::~BoundingBox()
	{
		
	}

	bool BoundingBox::hits(RayIntersection& outHitInfo, const Ray& ray)const
	{
		D64 t0;
		Vector3<D64> tMin, tMax;
		return findHitPoints(outHitInfo, ray, t0, tMin, tMax);
	}

	bool BoundingBox::hits(RayIntersection& outHitInfo, const Ray& ray,
		D64& t0, Vector3<D64>& tMin, Vector3<D64>& tMax)const
	{
		return findHitPoints(outHitInfo, ray, t0, tMin, tMax);
	}

	bool BoundingBox::findHitPoints(RayIntersection& outHitInfo, const Ray& ray, 
		D64& t0, Vector3<D64>& tMin, Vector3<D64>& tMax)const
	{
		VML::VECTOR3F o = ray.origin().asVector3();
		VML::VECTOR3F d = ray.direction().asVector3();

		for (I32 i = 0; i < 3; i++)
		{
			D64 v = 1.0 / d.v[i];
			if (v >= 0)
			{
				tMin.v[i] = (min.v[i] - o.v[i]) * v;
				tMax.v[i] = (max.v[i] - o.v[i]) * v;
			}
			else
			{
				tMin.v[i] = (max.v[i] - o.v[i]) * v;
				tMax.v[i] = (min.v[i] - o.v[i]) * v;
			}
		}

		// Find largest entering t value
		t0 = std::max(tMin.x, std::max(tMin.y, tMin.z));
		// Find smallest exiting t value
		D64 t1 = std::min(tMax.x, std::min(tMax.y, tMax.z));

		if (t0 < t1 && t1 > VML::FLOAT_EPSILON)
		{
			if (t0 >= 0.0f)
			{
				outHitInfo.t = t0;
				outHitInfo.worldCoords = ray.getPointAlongRay(t0);
			}
			else
			{
				outHitInfo.t = t1;
				outHitInfo.worldCoords = ray.getPointAlongRay(t1);
			}

			return true;
		}

		return false;
	}

	bool BoundingBox::isInside(const VML::Vector& point)const
	{
		VML::VECTOR3F p = point.asVector3();

		return p.x >= min.x && p.x <= max.x
			&& p.y >= min.y && p.y <= max.y
			&& p.z >= min.z && p.z <= max.z;
	}

	VML::VECTOR3F BoundingBox::center()const
	{
		return VML::VECTOR3F((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f, (min.z + max.z) / 2.0f);
	}

	U8 BoundingBox::longestAxis()const
	{
		VML::VECTOR3F extent(max.x - min.x, max.y - min.y, max.z - min.z);
		if (extent.x > extent.y && extent.x > extent.z)
			return 0;
		else if (extent.y > extent.z)
			return 1;
		return 2;
	}

	void BoundingBox::extend(const BoundingBox& other)
	{
		for (U8 i = 0; i < 3; i++)
		{
			min.v[i] = std::min(min.v[i], other.min.v[i]);
			max.v[i] = std::max(max.v[i], other.max.v[i]);
		}
	}
}