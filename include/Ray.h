#pragma once

#include <Util.h>
#include <VML.h>

namespace RT
{
	// Epsilon value to change shadow ray origins.
	const F32 RAY_EPSILON = (10 * VML::FLOAT_EPSILON);

	class Ray
	{
	public:
		// Creates a ray starting at the origin and moving in the (0, 0, 1) direction.
		Ray();

		// Creates a ray.
		// @param origin - The starting point of this ray.
		// @param direction - The direction of this ray.
		// @param epsilon - Move the origin of the ray a small amount in the direction of the ray.
		Ray(const VML::VECTOR3F& origin, const VML::VECTOR3F& direction);

		// Creates a ray.
		// @param origin - The starting point of this ray.
		// @param direction - The direction of this ray.
		Ray(const VML::Vector& origin, const VML::Vector& direction, F32 epsilon = 0.0f);

		// Default destructor.
		virtual ~Ray() = default;

		// Gets a point along the ray.
		// @param t - The distance from the ray's origin.
		VML::Vector GetPointAlongRay(F32 t)const;

		// Gets a copy of the origin point of this ray.
		VML::Vector origin()const;
		// Gets a copy of a direction vector of this ray.
		VML::Vector direction()const;

	private:
		VML::Vector o;
		VML::Vector d;
	};

	struct RayIntersection
	{
		RayIntersection() : t(F32_MAX) {}

		// Distance along the ray.
		F32 t;

		// World coordinates of intersection.
		VML::Vector worldCoords;

		// Normal vector at this intersection.
		VML::Vector normal;

		// UV coordinates
		VML::VECTOR2F uv;
	};
}