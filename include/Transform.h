#pragma once

#include <Util.h>
#include <VML.h>
#include <map>
#include <Ray.h>
#include <BoundingVolume.h>

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
		VML::Vector transformVector(const VML::Vector& v)const;
		BoundingBox transformBox(const BoundingBox& box)const;

		virtual ~Transform();

	public:

	private:
		void calculateMatrices(const VML::Vector& position, const VML::VECTOR3F& rotation, const VML::Vector scale);

	private:
		VML::Matrix m, inv, invT;
	};


	Transform LoadTransform(const std::string& params);
}