#pragma once

#include <BRDF.h>
#include <World.h>

namespace RT
{
	class Lambertian : public BRDF
	{
	public:
		Lambertian(F32 kd, const Color& cd);

		virtual ~Lambertian();

		virtual Color f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wo)const override;

	private:
		// Diffuse multiplier
		F32 kd;
		// Diffuse color
		Color cd;
	};

	class SVLambertian : public BRDF
	{
	public:
		SVLambertian(F32 kd, PTexture2D tex);

		virtual ~SVLambertian();

		virtual Color f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wo)const override;

	private:
		// Diffuse multiplier
		F32 kd;
		// Diffuse color
		PTexture2D tex;
	};

	class GlossySpecular : public BRDF
	{
	public:
		GlossySpecular(const Color& cs, F32 ks, F32 exp);

		virtual ~GlossySpecular();

		virtual Color f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const override;

		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wo)const override;

	private:
		// Specular color
		Color cs;
		// Specular multiplier
		F32 ks;
		// Specular exponent
		F32 exp;
	};

	class PerfectSpecular : public BRDF
	{
	public:
		PerfectSpecular(Color cr, F32 kr);

		virtual ~PerfectSpecular();

		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo)const override;

	private:
		Color cr;
		F32 kr;
	};
}