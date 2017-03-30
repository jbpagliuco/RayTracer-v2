#include <World.h>

namespace RT
{
	World::World()
	{

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


	bool World::traceRayColor(Color& out, const Ray& ray)
	{
		ElementIntersection hit;
		traceRayIntersections(hit, ray);

		if (hit.bHit)
		{
			out = hit.element->material->areaLightShade(hit, *this);
			return true;
		}

		return false;
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
					out.element = r;
					out.rayInt = hitInfo;
					out.ray = ray;
				}
			}
		}

		if (out.bHit)
		{
			out.rayInt.normal = out.element->transform.transformNormal(out.rayInt.normal);
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