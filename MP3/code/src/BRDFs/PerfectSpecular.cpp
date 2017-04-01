#include <BRDFTypes.h>

namespace RT
{
	PerfectSpecular::PerfectSpecular(Color cr, F32 kr) : cr(cr), kr(kr)
	{

	}

	PerfectSpecular::~PerfectSpecular()
	{

	}

	Color PerfectSpecular::sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const
	{
		F32 nDOTwo = ei.rayInt.normal.v3Dot(wo);
		wi = VML::Vector(wo).negate() + (ei.rayInt.normal * nDOTwo * 2.0f);

		return (cr * kr) / ei.rayInt.normal.v3Dot(wi);
	}
}