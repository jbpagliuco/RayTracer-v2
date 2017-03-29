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
		Transform(const VML::VECTOR3F& position, const VML::VECTOR3F& rotation, const VML::VECTOR3F& scale);

		Ray transformRay(const Ray& ray)const;
		VML::Vector transformNormal(const VML::Vector& normal)const;

		virtual ~Transform();

	public:
		VML::Vector position;
		VML::Vector scale;

	private:
		void calculateMatrices(const VML::Vector& position, const VML::VECTOR3F& rotation, const VML::Vector scale);

	private:
		VML::Matrix inv, invT;
	};


	Transform LoadTransform(const std::string& params);
}