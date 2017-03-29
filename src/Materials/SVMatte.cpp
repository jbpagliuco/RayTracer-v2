#include <MaterialTypes.h>

namespace RT
{
	SVMatte::SVMatte(F32 ka, F32 kd, PTexture2D tex) : ambientBRDF(ka, tex), diffuseBRDF(kd, tex) {}

	SVMatte::~SVMatte() {}

	Color SVMatte::shade(const ElementIntersection& ei, World& world)
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
			VML::Vector wi = light->getDirectionFromPoint(ei.rayInt.worldCoords).v3Normalize();
			F32 ndotwi = ei.rayInt.normal.v3Dot(wi);
			F32 ndotwo = ei.rayInt.normal.v3Dot(wo);

			if (ndotwo > 0.0f && ndotwi > 0.0f)
			{
				Ray shadowRay(ei.rayInt.worldCoords, wi, RAY_EPSILON);
				bool bInShadow = light->inShadow(shadowRay, ei, world);

				if (!bInShadow)
					color += diffuseBRDF.f(ei, wi, wo) * light->calculateRadiance(ei, world) * ndotwi;
			}
		}

		return color;
	}

	Color SVMatte::areaLightShade(const ElementIntersection& ei, World& world)
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


	PMaterial LoadSVMatteMaterial(std::stringstream& ss, World& world)
	{
		F32 ka, kd;
		std::string textureName;
		ss >> ka >> kd >> textureName;

		return std::make_shared<SVMatte>(ka, kd, world.assetManager.GetTexture2D(textureName));
	}
}