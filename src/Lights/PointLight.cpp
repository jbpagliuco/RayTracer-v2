#include <LightTypes.h>

namespace RT
{
	PointLight::PointLight()
	{

	}

	PointLight::PointLight(F32 ls, Color color, VML::Vector position, bool bCastsShadows) : 
		ls(ls), color(color), Light(bCastsShadows)
	{
		this->position = position;
	}

	PointLight::~PointLight()
	{

	}

	F32 PointLight::getDistanceFromPoint(const VML::Vector& point)const
	{
		return (position - point).v3Length();
	}

	VML::Vector PointLight::getDirectionFromPoint(const VML::Vector& point)
	{
		return (position - point).v3Normalize();
	}

	Color PointLight::calculateRadiance(const ElementIntersection& ei, const World& world)
	{
		return color * ls;
	}




	PLight LoadPointLight(std::stringstream& ss, World& world)
	{
		F32 ls;
		Color color;
		VML::VECTOR3F position;
		std::string castsShadows;

		ss >> ls >>
			color.r >> color.g >> color.b >>
			position.x >> position.y >> position.z >>
			castsShadows;

		return std::make_shared<PointLight>(ls, color, VML::Vector(position), castsShadows == "true");
	}
}