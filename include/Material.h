#pragma once

#include <Util.h>
#include <Color.h>
#include <map>

namespace RT
{
	// Forward declaration
	struct ElementIntersection;
	class World;

	class Material
	{
	public:
		Material();

		virtual ~Material();

		virtual Color shade(const ElementIntersection& ei, World& world);
		virtual Color areaLightShade(const ElementIntersection& ei, World& world);
	};
	
	typedef std::shared_ptr<Material> PMaterial;


	PMaterial LoadMaterial(const std::map<std::string, std::string>& params, World& world);
	PMaterial LoadMaterial(const std::string& params, World& world);
}