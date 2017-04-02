#include <ASTypes.h>

namespace RT
{
	RegularGrid::RegularGrid()
	{

	}

	RegularGrid::~RegularGrid()
	{

	}

	void RegularGrid::build(const std::vector<PASData>& objects)
	{
		// Calculate the grids bounding box
		calcBounds(objects);

		// Calculate the grid dimensions
		calcGridDimensions(objects.size());

		// Place each object in its cells
		placeObjects(objects);
	}




	bool RegularGrid::hits(ElementIntersection& outHitInfo, const Ray& ray)const
	{
		Vector3i cell;
		Vector3f d, next;
		Vector3i step, stop;
		bool bHit = traverseInit(cell, d, next, step, stop, ray);

		while (bHit)
		{
			// This cell's linear index
			I32 l = cell.x + n.x * cell.y + n.x * n.y * cell.z;

			bool bHitCell = false;
			if (cells.find(l) != cells.end())
				bHitCell = traceRay(outHitInfo, ray, cells.at(l));

			if (next.x < next.y && next.x < next.z)
			{
				if (bHitCell && (outHitInfo.rayInt.t < next.x))
					break;

				next.x += d.x;
				cell.x += step.x;

				if (cell.x == stop.x)
					break;
			}
			else if (next.y < next.z)
			{
				if (bHitCell && (outHitInfo.rayInt.t < next.y))
					break;

				next.y += d.y;
				cell.y += step.y;

				if (cell.y == stop.y)
					break;
			}
			else
			{
				if (bHitCell && (outHitInfo.rayInt.t < next.z))
					break;

				next.z += d.z;
				cell.z += step.z;

				if (cell.z == stop.z)
					break;
			}
		}

		return traceRay(outHitInfo, ray, unbounded);
	}

	bool RegularGrid::shadowHits(F32 d, const Ray& ray)const
	{
		Vector3i cell;
		Vector3f delta, next;
		Vector3i step, stop;
		bool bHit = traverseInit(cell, delta, next, step, stop, ray);

		while (bHit)
		{
			// This cell's linear index
			I32 l = cell.x + n.x * cell.y + n.x * n.y * cell.z;

			if (cells.find(l) != cells.end())
			{
				if (traceRay(d, ray, cells.at(l)))
					return true;
			}

			if (next.x < next.y && next.x < next.z)
			{
				next.x += delta.x;
				cell.x += step.x;

				if (cell.x == stop.x)
					break;
			}
			else if (next.y < next.z)
			{
				next.y += delta.y;
				cell.y += step.y;

				if (cell.y == stop.y)
					break;
			}
			else
			{
				next.z += delta.z;
				cell.z += step.z;

				if (cell.z == stop.z)
					break;
			}
		}

		return traceRay(d, ray, unbounded);
	}


	BoundingBox RegularGrid::getBoundingBox()const
	{
		return bounds;
	}










	void RegularGrid::calcBounds(const std::vector<PASData>& objects)
	{
		// Initialize bounding box to infinity
		bounds.min = VML::VECTOR3F(F32_MAX, F32_MAX, F32_MAX);
		bounds.max = VML::VECTOR3F(F32_NMAX, F32_NMAX, F32_NMAX);

		// Calculate the bounding box
		for (auto it = objects.begin(); it != objects.end(); it++)
		{
			PASData p = *it;
			if (p->geometry()->hasBounds())
			{
				BoundingBox t = p->bbox();
				if (p->hasTransform())
					t = p->transform().transformBox(t);
				bounds.extend(t);
			}
		}

		// Make bounding box slightly larger than all elements
		bounds.min.x -= F32_EPS; bounds.min.y -= F32_EPS; bounds.min.z -= F32_EPS;
		bounds.max.x += F32_EPS; bounds.max.y += F32_EPS; bounds.max.z += F32_EPS;
	}

	void RegularGrid::calcGridDimensions(I64 numObjects)
	{
		VML::VECTOR3F min = bounds.min, max = bounds.max;
		VML::VECTOR3F w(max.x - min.x, max.y - min.y, max.z - min.z);
		const F32 s = (F32)pow(w.x * w.y * w.z / numObjects, 0.33333333333333);
		const F32 m = 2.0f;
		n = Vector3i((I32)(m * w.x / s) + 1, (I32)(m * w.y / s) + 1, (I32)(m * w.z / s) + 1);
	}

	void RegularGrid::placeObjects(const std::vector<PASData>& objects)
	{
		// Place all the objects in their cells
		for (auto it = objects.begin(); it != objects.end(); it++)
		{
			PASData p = *it;

			if (p->geometry()->hasBounds())
				placeObject(p);
			else
				unbounded.push_back(p);
		}
	}

	Vector3i RegularGrid::calculateCell(const VML::VECTOR3F& point)const
	{
		Vector3i cell;
		for (I32 i = 0; i < 3; i++)
			cell.v[i] = (I32)Clamp((I32)((point.v[i] - bounds.min.v[i]) * n.v[i] / (bounds.max.v[i] - bounds.min.v[i])), 0, n.v[i] - 1);

		return cell;
	}

	bool RegularGrid::getStartingCell(Vector3i& cell, D64& t0, Vector3d& tMin, Vector3d& tMax, const Ray& ray)const
	{
		RayIntersection hit;
		bool bHit = bounds.hits(hit, ray, t0, tMin, tMax);

		if (!bHit)
			return false;

		VML::Vector p;
		if (bounds.isInside(ray.origin()))
			p = ray.origin();
		else
			p = ray.getPointAlongRay((F32)t0);

		cell = calculateCell(p.asVector3());
		return true;
	}

	void RegularGrid::placeObject(const PASData& p)
	{
		BoundingBox t = p->bbox();
		if (p->hasTransform())
			t = p->transform().transformBox(t);

		// Min and max cell values (x, y, z)
		Vector3i cMin = calculateCell(t.min);
		Vector3i cMax = calculateCell(t.max);

		for (I32 z = cMin.z; z <= cMax.z; z++)
		{
			for (I32 y = cMin.y; y <= cMax.y; y++)
			{
				for (I32 x = cMin.x; x <= cMax.x; x++)
				{
					I32 index = x + n.x * y + n.x * n.y * z;

					if (cells.find(index) == cells.end())
						cells[index] = std::vector<PASData>();

					cells[index].push_back(p);
				}
			}
		}
	}


	bool RegularGrid::traverseInit(
		Vector3i& cell, Vector3f& d, 
		Vector3f& next, Vector3i& step, Vector3i& stop, 
		const Ray& ray)const
	{
		D64 t0;
		Vector3d tMin, tMax;
		bool bHit = getStartingCell(cell, t0, tMin, tMax, ray);

		if (!bHit)
			return false;

		d = Vector3f((F32)(tMax.x - tMin.x) / n.x, (F32)(tMax.y - tMin.y) / n.y, (F32)(tMax.z - tMin.z) / n.z);
		VML::VECTOR3F dir = ray.direction().asVector3();

		for (I32 i = 0; i < 3; i++)
		{
			if (VML::FEquals(dir.v[i], 0.0f))
			{
				next.v[i] = F32_MAX;
				step.v[i] = -1;
				stop.v[i] = -1;
			}
			else if (dir.v[i] > 0)
			{
				next.v[i] = (F32)tMin.v[i] + (cell.v[i] + 1) * d.v[i];
				step.v[i] = +1;
				stop.v[i] = n.v[i];
			}
			else
			{
				next.v[i] = (F32)tMin.v[i] + (n.v[i] - cell.v[i]) * d.v[i];
				step.v[i] = -1;
				stop.v[i] = -1;
			}
		}

		return true;
	}


	bool RegularGrid::traceRay(ElementIntersection& out, const Ray& ray, const std::vector<PASData>& objects)const
	{
		// Keep track of the closest element
		F32 minDepth = out.bHit ? out.rayInt.t : F32_MAX;

		for (auto it = objects.begin(); it != objects.end(); it++)
		{
			PASData p = *it;

			RayIntersection hitInfo;
			bool bHit = p->geometry()->hits(hitInfo, p->transform().transformRay(ray));
			if (bHit)
			{
				// Depth test
				if (hitInfo.t < minDepth)
				{
					out.bHit = true;
					out.element = p;
					out.rayInt = hitInfo;
					out.ray = ray;

					minDepth = hitInfo.t;
				}
			}
		}

		

		return out.bHit;
	}

	bool RegularGrid::traceRay(D64 d, const Ray& ray, const std::vector<PASData>& objects)const
	{
		for (auto it = objects.begin(); it != objects.end(); it++)
		{
			PASData p = *it;

			F32 t;
			bool bHit = p->geometry()->shadowHits(t, p->transform().transformRay(ray));
			if (bHit && t < d)
				return true;
		}
		
		return false;
	}
}