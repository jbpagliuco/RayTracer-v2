#include <LightTypes.h>

namespace RT
{
	ParallelLight::ParallelLight()
	{

	}

	ParallelLight::ParallelLight(F32 ls, Color color, VML::Vector direction, bool bCastsShadows) : 
		ls(ls), color(color), Light(bCastsShadows)
	{
		this->direction = direction.v3Normalize();
	}

	ParallelLight::~ParallelLight()
	{

	}

	F32 ParallelLight::getDistanceFromPoint(const VML::Vector& point)const
	{
		return F32_INF;
	}

	VML::Vector ParallelLight::getDirectionFromPoint(const VML::Vector& point)
	{
		return direction;
	}

	Color ParallelLight::calculateRadiance(const ElementIntersection& ei, const World& world)
	{
		return color * ls;
	}



	PLight LoadParallelLight(std::stringstream& ss, World& world)
	{
		F32 ls;
		Color color;
		VML::VECTOR4F direction(0.0f, 0.0f, 0.0f, 0.0f);
		std::string castsShadows;

		ss >> ls >>
			color.r >> color.g >> color.b >>
			direction.x >> direction.y >> direction.z >> 
			castsShadows;

		return std::make_shared<ParallelLight>(ls, color, VML::Vector(direction), castsShadows == "true");
	}
}