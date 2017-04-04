#include <MaterialTypes.h>

namespace RT
{
	Reflective::Reflective(F32 ka, F32 kd, const Color& cd, F32 ks, const Color& cs, F32 exp, const Color& cr, F32 kr) :
		reflectiveBRDF(cr, kr), Phong(ka, kd, cd, ks, cs, exp)
	{

	}
	
	Reflective::~Reflective()
	{

	}

	Color Reflective::shade(const ElementIntersection& ei, World& world)
	{
		Color color(Phong::shade(ei, world));

		VML::Vector wo = ei.ray.direction().negate();
		VML::Vector wi;
		Color fr = reflectiveBRDF.sampleF(ei, wi, wo);
		Ray reflectedRay(ei.rayInt.worldCoords, wi);

		color += fr * world.traceRayColor(reflectedRay, ei.depth + 1) * (ei.rayInt.normal.v3Dot(wi));

		return color;
	}

	Color Reflective::areaLightShade(const ElementIntersection& ei, World& world)
	{
		Color color = Phong::shade(ei, world);

		VML::Vector wo = ei.ray.direction().negate();
		VML::Vector wi;
		Color fr = reflectiveBRDF.sampleF(ei, wi, wo);
		Ray reflectedRay(ei.rayInt.worldCoords, wi);

		color += fr * world.traceRayColor(reflectedRay, ei.depth + 1) * (ei.rayInt.normal.v3Dot(wi));

		return color;
	}




	PMaterial LoadReflectiveMaterial(std::stringstream& ss, World& world)
	{
		F32 ka, kd, ks, exp, kr;
		Color cd, cs, cr;
		ss >> ka >> kd >> cd.r >> cd.g >> cd.b >> cd.a
			>> ks >> cs.r >> cs.g >> cs.b >> cs.a >> exp
			>> kr >> cr.r >> cr.g >> cr.b >> cr.a;

		return std::make_shared<Reflective>(ka, kd, cd, ks, cs, exp, cr, kr);
	}
}