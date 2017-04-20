#include <MaterialTypes.h>

namespace RT
{
	Transparent::Transparent(
		F32 ka, F32 kd, const Color& cd,
		F32 ks, const Color& cs, F32 exp,
		const Color& cr, F32 kr, F32 kt, F32 ior)
		: Phong(ka, kd, cd, ks, cs, exp), reflectiveBRDF(cr, kr), specularBTDF(kt, ior)
	{
	}

	Transparent::~Transparent()
	{

	}

	Color Transparent::shade(const ElementIntersection& ei, World& world)
	{
		Color color(Phong::shade(ei, world));

		VML::Vector wo = ei.ray.direction();
		wo.negate();
		VML::Vector wi;
		
		Color fr = reflectiveBRDF.sampleF(ei, wi, wo);
		Ray reflectedRay(ei.rayInt.worldCoords, wi);

		if (specularBTDF.tir(ei))
			color += world.traceRayColor(reflectedRay, ei.depth + 1);
		else
		{
			VML::Vector wt;
			Color ft = specularBTDF.sampleF(ei, wt, wo);
			Ray transmittedRay(ei.rayInt.worldCoords, wt);

			color += fr * world.traceRayColor(reflectedRay, ei.depth + 1) * fabs(ei.rayInt.normal.v3Dot(wi));
			color += ft * world.traceRayColor(transmittedRay, ei.depth + 1) * fabs(ei.rayInt.normal.v3Dot(wt));
		}

		return color;
	}

	Color Transparent::areaLightShade(const ElementIntersection& ei, World& world)
	{
		return Color();
	}





	PMaterial LoadTransparentMaterial(std::stringstream& ss, World& world)
	{
		F32 ka, kd, ks, exp, kr, kt, ior;
		Color cd, cs, cr;
		ss >> ka >> kd >> cd.r >> cd.g >> cd.b >> cd.a
			>> ks >> cs.r >> cs.g >> cs.b >> cs.a >> exp
			>> kr >> cr.r >> cr.g >> cr.b >> cr.a
			>> kt >> ior;

		return std::make_shared<Transparent>(ka, kd, cd, ks, cs, exp, cr, kr, kt, ior);
	}
}