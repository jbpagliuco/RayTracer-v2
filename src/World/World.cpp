#include <World.h>

namespace RT
{
	World::World()
	{

	}


	void World::addRenderable(PRenderable r)
	{
		renderables.push_back(r);
	}

	Renderables& World::getRenderables()
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
		return false;
	}


	void World::traceRayIntersections(ElementIntersection& out, const Ray& ray)const
	{

	}

	void World::traceRayIntersections(bool& bHit, F32 d, const Ray& ray)const
	{

	}
}