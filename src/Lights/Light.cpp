#include <Light.h>

#include <World.h>
#include <algorithm>
#include <LightTypes.h>
#include <AmbientLights.h>

namespace RT
{
	Light::Light(bool bCastsShadows) : bCastsShadows(bCastsShadows) {}

	Light::~Light() {}

	bool Light::inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const
	{
		if (!bCastsShadows)
			return false;

		F32 d = getDistanceFromPoint(ray.origin());

		bool bHit;
		world.traceRayIntersections(bHit, d, ray);

		return bHit;
	}

	F32 Light::g(const ElementIntersection& ei)const
	{
		return 0.0f;
	}

	F32 Light::pdf(const ElementIntersection& ei)const
	{
		return 0.0f;
	}





	typedef PLight(*LightLoader)(std::stringstream&, World&);
	std::map<std::string, LightLoader> loaders = {
		{ "ambient", LoadAmbientLight },
		{ "ambientOccluder", LoadAmbientOccluderLight },
		{ "parallel", LoadParallelLight },
		{ "point", LoadPointLight },
		{ "area", LoadAreaLight }
	};

	PLight LoadLight(const std::map<std::string, std::string>& params, World& world)
	{
		std::string type = params.at("type");
		std::stringstream ss(params.at("params"));

		return loaders[type](ss, world);
	}

	PLight LoadLight(const std::string& params, World& world)
	{
		std::stringstream ss(params);

		std::map<std::string, std::string> p;
		ss >> p["type"];

		std::string curr;
		while (!(ss >> curr).eof())
			p["params"] += curr + " ";
		p["params"] += curr;

		return LoadLight(p, world);
	}
}