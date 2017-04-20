#pragma once

#include <Material.h>

#include <World.h>
#include <BRDFTypes.h>
#include <BTDFTypes.h>

namespace RT
{
	class Matte : public Material
	{
	public:
		// Creates a matte material.
		// @param ka - The ambient factor.
		// @param kd - The diffuse factor.
		// @param cd - The diffuse color.
		Matte(F32 ka, F32 kd, const Color& cd);

		virtual ~Matte();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

	private:
		Lambertian ambientBRDF;
		Lambertian diffuseBRDF;
	};
	PMaterial LoadMatteMaterial(std::stringstream& ss, World& world);

	class SVMatte : public Material
	{
	public:
		// Creates a matte material.
		// @param ka - The ambient factor.
		// @param kd - The diffuse factor.
		// @param pTex - A pointer to the texture to use.
		SVMatte(F32 ka, F32 kd, PTexture2D tex);

		virtual ~SVMatte();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

	private:
		SVLambertian ambientBRDF;
		SVLambertian diffuseBRDF;
	};
	PMaterial LoadSVMatteMaterial(std::stringstream& ss, World& world);

	class Phong : public Material
	{
	public:
		// Creates a matte material.
		// @param ka - The ambient factor.
		// @param kd - The diffuse factor.
		// @param cd - The diffuse color.
		// @param ks - The specular factor.
		// @param cs - The specular color.
		// @param exp - The specular exponent.
		Phong(F32 ka, F32 kd, const Color& cd, F32 ks, const Color& cs, F32 exp);

		virtual ~Phong();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

	private:
		Lambertian ambientBRDF;
		Lambertian diffuseBRDF;
		GlossySpecular specularBRDF;
	};
	PMaterial LoadPhongMaterial(std::stringstream& ss, World& world);

	class Emissive : public Material
	{
	public:
		Emissive(F32 ls, Color c);

		virtual ~Emissive();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

		Color getLe()const;

	private:
		Color c;
		F32 ls;
	};
	PMaterial LoadEmissiveMaterial(std::stringstream& ss, World& world);

	class Reflective : public Phong
	{
	public:
		Reflective(F32 ka, F32 kd, const Color& cd, F32 ks, const Color& cs, F32 exp, const Color& cr, F32 kr);

		virtual ~Reflective();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

	private:
		PerfectSpecular reflectiveBRDF;
	};
	PMaterial LoadReflectiveMaterial(std::stringstream& ss, World& world);


	class GlossyReflector : public Phong
	{
	public:
		GlossyReflector(F32 ka, F32 kd, const Color& cd, F32 ks, const Color& cs, F32 exp, const Color& cr, F32 kr);

		virtual ~GlossyReflector();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

	private:
		GlossySpecular glossyBRDF;
	};
	PMaterial LoadGlossyReflectorMaterial(std::stringstream& ss, World& world);


	class Transparent : public Phong
	{
	public:
		Transparent(F32 ka, F32 kd, const Color& cd, F32 ks, const Color& cs, F32 exp, 
			const Color& cr, F32 kr, F32 kt, F32 ior);

		virtual ~Transparent();

		virtual Color shade(const ElementIntersection& ei, World& world)override;
		virtual Color areaLightShade(const ElementIntersection& ei, World& world)override;

	private:
		PerfectSpecular reflectiveBRDF;
		PerfectTransmitter specularBTDF;
	};
	PMaterial LoadTransparentMaterial(std::stringstream& ss, World& world);
}