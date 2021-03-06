#pragma once

#include <Ray.h>
#include <VML.h>
#include <Util.h>

namespace RT
{
	class BoundingVolume
	{
	public:
		// Default constructor.
		BoundingVolume() = default;

		// Default destructor.
		virtual ~BoundingVolume() = default;

		// Checks to see if a ray intersects this bounding volume.
		// @param [out] outHitInfo - The intersection point.
		// @param ray - The ray to check against.
		// @return Does the ray intersect this bounding volume?
		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const = 0;
	};

	class BoundingBox : BoundingVolume
	{
	public:
		BoundingBox();
		BoundingBox(const VML::VECTOR3F& min, const VML::VECTOR3F& max, bool bAddEpsilon = false);

		virtual ~BoundingBox();

		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray, D64& t0, Vector3<D64>& tMin, Vector3<D64>& tMax)const;
		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray,
			D64& t0, D64& t1, Vector3<D64>& tMin, Vector3<D64>& tMax, Vector3d& abc)const;

		// Is this point inside of this box?
		// @param point - The point to check.
		virtual bool isInside(const VML::Vector& point)const;

		// Returns the center coordinate of this bounding volume.
		VML::VECTOR3F center()const;

		// Returns the longest axis of this bounding volume.
		U8 longestAxis()const;

		// Extends this bounding box.
		// @param other - The bounding box to extend to.
		void extend(const BoundingBox& other);

	private:
		bool findHitPoints(RayIntersection& outHitInfo, const Ray& ray, 
			D64& t0, D64& t1, Vector3<D64>& tMin, Vector3<D64>& tMax, Vector3d& abc)const;

	public:
		VML::VECTOR3F min, max;
	};
}