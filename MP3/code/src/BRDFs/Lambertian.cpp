#include <BRDFTypes.h>

#include <World.h>

namespace RT
{
	Lambertian::Lambertian(F32 kd, const Color& cd) : kd(kd), cd(cd) {}

	Lambertian::~Lambertian() {}

	Color Lambertian::f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		return cd * kd * (F32)INV_PI;
	}

	Color Lambertian::sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const
	{
		return Color();
	}

	Color Lambertian::rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		return cd * kd;
	}

	Color Lambertian::rho(const ElementIntersection& ei, const VML::Vector& wo)const
	{
		return cd * kd;
	}
}