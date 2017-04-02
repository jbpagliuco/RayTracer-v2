#pragma once

#include <VML.h>
#include <Util.h>
#include <Transform.h>
#include <map>
#include <BoundingVolume.h>
#include <Ray.h>
#include <Sampler.h>

namespace RT
{
	struct ElementIntersection;
	class World;

	class Geometry
	{
	public:
		virtual ~Geometry() = default;

		// Checks to see if a ray intersects this geometry.
		// @param [out] outHitInfo - A list of the intersection points.
		// @param ray - The ray to check against.
		// @return Does the ray intersect this geometry?
		virtual bool hits(RayIntersection& outHitInfo, const Ray& ray)const = 0;

		// Checks to see if a ray intersects this geometry, but doesn't calculate any normals, etc.
		// @param [out] t - The t value for this ray, if there is an intersection point.
		// @param ray - The ray to check against.
		// @return Does the ray intersect this geometry?
		virtual bool shadowHits(F32& t, const Ray& ray)const = 0;

		// Gets the bounding box for this geometry.
		virtual BoundingBox getBoundingBox()const;
		
		// Can this object be bounded? (ie planes cannot)
		virtual bool hasBounds()const;

		virtual F32 pdf(const ElementIntersection& ei, const Transform& transform)const;

		virtual VML::Vector sample();

		virtual VML::Vector getNormalAtPoint(const VML::Vector& point)const;
	};

	typedef std::shared_ptr<Geometry> PGeometry;

	PGeometry LoadGeometry(const std::map<std::string, std::string>& params, World& world);
	PGeometry LoadGeometry(const std::string& params, World& world);
}