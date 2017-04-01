#include <Material.h>

#include <sstream>
#include <World.h>
#include <MaterialTypes.h>

namespace RT
{
	Material::Material()
	{

	}

	Material::~Material()
	{

	}
	
	Color Material::shade(const ElementIntersection& ei, World& world)
	{
		return Color();
	}

	Color Material::areaLightShade(const ElementIntersection& ei, World& world)
	{
		return Color();
	}





	typedef PMaterial (*MaterialLoader)(std::stringstream&, World&);
	std::map<std::string, MaterialLoader> loaders = {
		{ "matte", LoadMatteMaterial },
		{ "svmatte", LoadSVMatteMaterial },
		{ "phong", LoadPhongMaterial },
		{ "emissive", LoadEmissiveMaterial },
		{ "reflective", LoadReflectiveMaterial }
	};

	PMaterial LoadMaterial(const std::map<std::string, std::string>& params, World& world)
	{
		std::string type = params.at("type");
		std::stringstream ss(params.at("params"));

		return loaders[type](ss, world);
	}


	PMaterial LoadMaterial(const std::string& params, World& world)
	{
		std::stringstream ss(params);

		std::map<std::string, std::string> p;
		ss >> p["type"];

		std::string curr;
		while (!(ss >> curr).eof())
			p["params"] += curr + " ";
		p["params"] += curr;

		return LoadMaterial(p, world);
	}
}