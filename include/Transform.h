#pragma once

#include <Util.h>
#include <VML.h>
#include <map>
#include <Ray.h>

namespace RT
{
	// The positional/rotation representation of a Renderable.
	class Transform
	{
	public:
		Transform();
		// Creates a transform with the given position.
		// @param position - The position, in world coordinates.
		Transform(const VML::VECTOR3F& position);
		// Creates a transform with the given position.
		// @param position - The position, in world coordinates.
		Transform(const VML::Vector& position);

		Ray TransformRay(const Ray& ray)const;

		virtual ~Transform();

	public:
		VML::Vector position;
	};


	Transform LoadTransform(const std::string& params);
}