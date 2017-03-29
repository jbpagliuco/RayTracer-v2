#include <MaterialTypes.h>

namespace RT
{
	Phong::Phong(F32 ka, F32 kd, const Color& cd, F32 ks, const Color& cs, F32 exp) : 
		ambientBRDF(ka, cd), diffuseBRDF(kd, cd), specularBRDF(cs, ks, exp)
	{
	}

	Phong::~Phong() { }

	Color Phong::shade(const ElementIntersection& ei, World& world)
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
				{
					Color f = diffuseBRDF.f(ei, wi, wo) + specularBRDF.f(ei, wi, wo);
					color += f * light->calculateRadiance(ei, world) * ndotwi;
				}
			}
		}

		return color;
	}

	Color Phong::areaLightShade(const ElementIntersection& ei, World& world)
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
				{
					Color f = diffuseBRDF.f(ei, wi, wo) + specularBRDF.f(ei, wi, wo);
					color += f * light->calculateRadiance(ei, world) *
						light->g(ei) * ndotwi / light->pdf(ei);
				}
			}
		}

		return color;
	}



	PMaterial LoadPhongMaterial(std::stringstream& ss, World& world)
	{
		F32 ka, kd, ks, exp;
		Color cd, cs;
		ss >> ka >> kd >> cd.r >> cd.g >> cd.b >> cd.a
			>> ks >> cs.r >> cs.g >> cs.b >> cs.a >> exp;

		return std::make_shared<Phong>(ka, kd, cd, ks, cs, exp);
	}
}