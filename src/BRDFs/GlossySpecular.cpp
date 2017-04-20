#include <BRDFTypes.h>

namespace RT
{
	GlossySpecular::GlossySpecular(const Color& cs, F32 ks, F32 exp) : cs(cs), ks(ks), exp(exp)
	{
		sampler.mapSamplesToHemisphere(exp);
	}

	GlossySpecular::~GlossySpecular()
	{

	}

	Color GlossySpecular::f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		VML::Vector nWi = wi;
		nWi.negate();

		F32 ndotwi = ei.rayInt.normal.v3Dot(wi);
		VML::Vector r(nWi + ei.rayInt.normal * 2.0f * ndotwi);
		F32 rdotwo = r.v3Dot(wo);

		if (rdotwo > 0.0f)
			return cs * ks * pow(rdotwo, exp);
		return Color();
	}

	Color GlossySpecular::sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)
	{
		F32 nDOTwo = ei.rayInt.normal.v3Dot(wo);
		VML::Vector r = VML::Vector(wo).negate() + ei.rayInt.normal * nDOTwo * 2.0f;

		VML::Vector w = r;
		VML::Vector u = VML::Vector(0.00424f, 1.0f, 0.00764f, 0.0f).v3Cross(w).v3Normalize();
		VML::Vector v = u.v3Cross(w);

		VML::VECTOR3F sp = sampler.sampleHemisphere();
		wi = (u * sp.x) + (v * sp.y) + (w * sp.z);

		if (ei.rayInt.normal.v3Dot(wi) < 0.0f)
			wi = (u * -sp.x) + (v * -sp.y) + (w * sp.z);

		F32 phongLobe = pow(r.v3Dot(wi), exp);
		
		return cs * ks * phongLobe;
	}

	Color GlossySpecular::rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const
	{
		return Color();
	}

	Color GlossySpecular::rho(const ElementIntersection& ei, const VML::Vector& wo)const
	{
		return Color();
	}
}