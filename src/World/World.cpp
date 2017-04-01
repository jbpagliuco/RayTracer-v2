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
		out.bHit = acc->hits(out, ray);
	}

	void World::traceRayIntersections(bool& bHit, F32 d, const Ray& ray)const
	{
		bHit = acc->shadowHits(d, ray);
	}
}