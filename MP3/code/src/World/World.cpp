#include <World.h>

#include <ASTypes.h>

namespace RT
{
	World::World()
	{
		acc = std::make_unique<RegularGrid>();
	}


	void World::addRenderable(PRenderable r)
	{
		renderables[r->name] = r;
	}

	std::map<std::string, PRenderable>& World::getRenderables()
	{
		return renderables;
	}


	void World::addLight(PLight light)
	{
		// Ambient lights are null, since they are set directly in world
		if (light)
			lights.push_back(light);
	}

	Lights& World::getLights()
	{
		return lights;
	}


	void World::setCamera(PCamera camera)
	{
		this->camera = camera;
	}

	PCamera World::getCamera()
	{
		return camera;
	}


	Color World::traceRayColor(const Ray& ray, I32 depth)
	{
		if (depth > 7)
			return Color();

		ElementIntersection hit;
		traceRayIntersections(hit, ray);
		PASData p = hit.element;
		WorldASData* r = (WorldASData*)p.get();

		if (hit.bHit)
		{
			hit.depth = depth;
			return r->r->material->shade(hit, *this);
		}

		return camera->backgroundColor;
	}


	void World::traceRayIntersections(ElementIntersection& out, const Ray& ray)const
	{
		// Keep track of the closest element
		out.rayInt.t = F32_MAX;

		for (auto it = renderables.begin(); it != renderables.end(); it++)
		{
			auto r = it->second;

			RayIntersection hitInfo;
			bool bHit = r->geometry->hits(hitInfo, r->transform.transformRay(ray));
			if (bHit)
			{
				// Depth test
				if (hitInfo.t < out.rayInt.t)
				{
					out.bHit = true;
					out.element = std::make_shared<WorldASData>(r);
					out.rayInt = hitInfo;
					out.ray = ray;
				}
			}
		}

		if (out.bHit)
		{
			out.rayInt.normal = out.element->transform().transformNormal(out.rayInt.normal);
			if (out.rayInt.normal.v3Dot(ray.direction().negate()) < 0.0f)
				out.rayInt.normal.negate();

			out.rayInt.worldCoords = ray.getPointAlongRay(out.rayInt.t);
		}
	}

	void World::traceRayIntersections(bool& bHit, F32 d, const Ray& ray)const
	{
		for (auto it = renderables.begin(); it != renderables.end(); it++)
		{
			auto r = it->second;

			F32 t;
			bool bHit = r->geometry->shadowHits(t, r->transform.transformRay(ray));
			if (bHit && t < d)
			{
				bHit = true;
				return;
			}
		}

		bHit = false;
	}
}