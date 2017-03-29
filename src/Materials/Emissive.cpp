#include <MaterialTypes.h>
#include <World.h>

namespace RT
{
	Emissive::Emissive(F32 ls, Color c) : ls(ls), c(c) {}

	Emissive::~Emissive() {}

	Color Emissive::shade(const ElementIntersection& ei, World& world)
	{
		VML::Vector nNormal = ei.rayInt.normal;
		nNormal.negate();
		if (nNormal.v3Dot(ei.ray.direction()) > 0.0f)
			return c * ls;
		else
			return Color();
	}

	Color Emissive::areaLightShade(const ElementIntersection& ei, World& world)
	{
		VML::Vector nNormal = ei.rayInt.normal;
		nNormal.negate();
		if (nNormal.v3Dot(ei.ray.direction()) > 0.0f)
			return c * ls;
		else
			return Color();
	}

	Color Emissive::getLe()const
	{
		return c * ls;
	}



	PMaterial LoadEmissiveMaterial(std::stringstream& ss, World& world)
	{
		F32 ls;
		Color c;

		ss >> ls >> c.r >> c.g >> c.b;
		c.a = 1.0f;

		return std::make_shared<Emissive>(ls, c);
	}
}