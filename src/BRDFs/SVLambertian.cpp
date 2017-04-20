#include <BRDFTypes.h>

namespace RT
{
	SVLambertian::SVLambertian(F32 kd, PTexture2D tex) : kd(kd), tex(tex)
	{

	}

	SVLambertian::~SVLambertian()
	{

	}

	Color SVLambertian::f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		Color cd = tex->getColor(ei.rayInt.uv.x, ei.rayInt.uv.y);
		return cd * kd * (F32)INV_PI;
	}

	Color SVLambertian::sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)
	{
		return Color();
	}

	Color SVLambertian::rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		Color cd = tex->getColor(ei.rayInt.uv.x, ei.rayInt.uv.y);
		return cd * kd;
	}

	Color SVLambertian::rho(const ElementIntersection& ei, const VML::Vector& wo)const
	{
		Color cd = tex->getColor(ei.rayInt.uv.x, ei.rayInt.uv.y);
		return cd * kd;
	}
}