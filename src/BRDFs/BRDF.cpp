#include <BRDF.h>

namespace RT
{
	BRDF::BRDF()
	{

	}

	BRDF::~BRDF()
	{

	}

	Color BRDF::f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		return Color();
	}

	Color BRDF::sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const
	{
		return Color();
	}

	Color BRDF::rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		return Color();
	}

	Color BRDF::rho(const ElementIntersection& ei, const VML::Vector& wo)const
	{
		return Color();
	}
}