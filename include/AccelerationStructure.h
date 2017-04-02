#pragma once

#include <Geometry.h>

namespace RT
{
	class ASData
	{
	public:
		ASData() = default;
		virtual ~ASData() = default;

		virtual PGeometry geometry()const = 0;
		virtual BoundingBox bbox()const = 0;
		virtual Transform transform()const = 0;
		virtual bool hasTransform()const;
	};
	typedef std::shared_ptr<ASData> PASData;


	// Output of a ray trace intersection
	struct ElementIntersection
	{
		ElementIntersection() : bHit(false), depth(0) { }

		bool bHit;
		PASData element;
		RayIntersection rayInt;
		Ray ray;
		I32 depth;
	};



	class AccelerationStructure
	{
	public:
		AccelerationStructure() = default;

		virtual ~AccelerationStructure() = default;

		virtual void build(const std::vector<PASData>& objects) = 0;

		virtual bool hits(ElementIntersection& outHitInfo, const Ray& ray)const = 0;
		virtual bool shadowHits(F32 d, const Ray& ray)const = 0;

		virtual BoundingBox getBoundingBox()const = 0;
	};
	typedef std::unique_ptr<AccelerationStructure> PAccelerationStructure;
}