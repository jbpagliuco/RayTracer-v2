#include <MaterialTypes.h>

namespace RT
{
	Matte::Matte(F32 ka, F32 kd, const Color& cd) : ambientBRDF(ka, cd), diffuseBRDF(kd, cd) {}

	Matte::~Matte() {}

	Color Matte::shade(const ElementIntersection& ei, World& world)
	{
		VML::Vector wo = ei.ray.direction().negate();

		// Add ambient light
		Color color;
		if (world.ambient)
			color += ambientBRDF.rho(ei, wo) * world.ambient->calculateRadiance(ei, world);

		// Add color from each light
		auto lights = world.getLights();
		for (auto it = lights.begin(); it != lights.end(); it++)
		{
			auto light = *it;
			VML::Vector wi = light->getDirectionFromPoint(ei.rayInt.worldCoords);
			F32 ndotwi = ei.rayInt.normal.v3Dot(wi);

			if (ndotwi > 0.0f)
			{
				Ray shadowRay(ei.rayInt.worldCoords, wi, RAY_EPSILON);
				bool bInShadow = light->inShadow(shadowRay, ei, world);

				if (!bInShadow)
					color += diffuseBRDF.f(ei, wi, wo) * light->calculateRadiance(ei, world) * ndotwi;
			}
		}

		return color;
	}

	Color Matte::areaLightShade(const ElementIntersection& ei, World& world)
	{
		VML::Vector wo = ei.ray.direction().negate();

		// Add ambient light
		Color color;
		if (world.ambient)
			color += ambientBRDF.rho(ei, wo) * world.ambient->calculateRadiance(ei, world);

		// Add color from each light
		auto lights = world.getLights();
		for (auto it = lights.begin(); it != lights.end(); it++)
		{
			auto light = *it;
			VML::Vector wi = light->getDirectionFromPoint(ei.rayInt.worldCoords);
			F32 ndotwi = ei.rayInt.normal.v3Dot(wi);

			if (ndotwi > 0.0f)
			{
				Ray shadowRay(ei.rayInt.worldCoords, wi, RAY_EPSILON);
				bool bInShadow = light->inShadow(shadowRay, ei, world);

				if (!bInShadow)
					color += diffuseBRDF.f(ei, wi, wo) * light->calculateRadiance(ei, world) *
					light->g(ei) * ndotwi / light->pdf(ei);
			}
		}

		return color;
	}


	PMaterial LoadMatteMaterial(std::stringstream& ss, World& world)
	{
		F32 ka, kd;
		Color color;
		ss >> ka >> kd >> color.r >> color.g >> color.b >> color.a;

		return std::make_shared<Matte>(ka, kd, color);
	}
}