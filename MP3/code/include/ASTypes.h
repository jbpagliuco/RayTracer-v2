#pragma once

#include <AccelerationStructure.h>

namespace RT
{
	class RegularGrid : public AccelerationStructure
	{
	public:
		RegularGrid();

		virtual ~RegularGrid();

		virtual void build(const std::vector<PASData>& objects) override;
		
		virtual bool hits(ElementIntersection& outHitInfo, const Ray& ray)const override;
		virtual bool shadowHits(F32 d, const Ray& ray)const override;

	protected:
		void calcBounds(const std::vector<PASData>& objects);
		void calcGridDimensions(I64 numObjects);
		void placeObjects(const std::vector<PASData>& objects);

		Vector3i calculateCell(const VML::VECTOR3F& point)const;
		bool getStartingCell(Vector3i& cell, D64& t0, Vector3d& tMin, Vector3d& tMax, const Ray& ray)const;

		void placeObject(const PASData& object);

	private:
		bool traverseInit(Vector3i& cell, Vector3f& d, Vector3f& next, Vector3i& step, Vector3i& stop, const Ray& ray)const;

		bool traceRay(ElementIntersection& out, const Ray& ray, const std::vector<PASData>& objects)const;
		bool traceRay(D64 d, const Ray& ray, const std::vector<PASData>& objects)const;

	protected:
		BoundingBox bounds;
		Vector3i n;

		std::map<I32, std::vector<PASData>> cells;
		std::vector<PASData> unbounded;
	};
}