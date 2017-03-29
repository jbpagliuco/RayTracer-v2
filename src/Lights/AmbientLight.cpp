#include <LightTypes.h>

#include <World.h>

namespace RT
{
	AmbientLight::AmbientLight() {}

	AmbientLight::AmbientLight(F32 ls, Color color) : ls(ls), color(color) {}

	AmbientLight::~AmbientLight() {}
	
	F32 AmbientLight::getDistanceFromPoint(const VML::Vector& point)const
	{
		return 0.0f;
	}

	VML::Vector AmbientLight::getDirectionFromPoint(const VML::Vector& point)
	{
		return VML::VectorZero();
	}

	Color AmbientLight::calculateRadiance(const ElementIntersection& ei, const World& world)
	{
		return color * ls;
	}

	bool AmbientLight::inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const
	{
		return false;
	}



	PLight LoadAmbientLight(std::stringstream& ss, World& world)
	{
		F32 ls;
		Color color;

		ss >> ls >> color.r >> color.g >> color.b;

		world.ambient = AllocateAligned16(AmbientLight(ls, color));
		return nullptr;
	}
}