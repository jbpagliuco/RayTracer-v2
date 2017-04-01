#pragma once

#include <Transform.h>
#include <Geometry.h>
#include <Material.h>

namespace RT
{
	// A renderable element (sphere, tri, etc)
	struct Renderable
	{
		Renderable() {}
		// Constructor.
		// @param name - The name of the world element.
		Renderable(const std::string& name) : name(name) {}

	public:
		std::string name;

		Transform transform;
		PGeometry geometry;
		PMaterial material;
	};

	typedef std::shared_ptr<Renderable> PRenderable;
	typedef std::vector<PRenderable> Renderables;
}