#pragma once

#include <Light.h>
#include <World.h>

namespace RT
{
	class ParallelLight : public Light
	{
	public:
		ParallelLight();

		// Creates a parallel light.
		// @param ls - The multiplicative factor.
		// @param color - The color of this light.
		// @param direction - The direction for this light.
		ParallelLight(F32 ls, Color color, VML::Vector direction, bool bCastsShadows);

		virtual ~ParallelLight();

		virtual F32 getDistanceFromPoint(const VML::Vector& point)const override;
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point)override;

		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world)override;

	protected:
		VML::Vector direction;
		Color color;
		F32 ls;
	};
	PLight LoadParallelLight(std::stringstream&, World&);

	class PointLight : public Light
	{
	public:
		PointLight();

		// Creates a point light.
		// @param ls - The multiplicative factor.
		// @param color - The color of this light.
		// @param position - The position of this light.
		PointLight(F32 ls, Color color, VML::Vector position, bool bCastsShadows);

		virtual ~PointLight();

		virtual F32 getDistanceFromPoint(const VML::Vector& point)const override;
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point)override;

		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world)override;

	protected:
		VML::Vector position;
		Color color;
		F32 ls;
	};
	PLight LoadPointLight(std::stringstream&, World&);

	class AreaLight : public Light
	{
	public:
		// Creates an area light.
		AreaLight(PRenderable renderable);

		virtual ~AreaLight();

		virtual F32 getDistanceFromPoint(const VML::Vector& point)const override;
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point)override;

		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world)override;

		virtual F32 g(const ElementIntersection& ei)const override;

		virtual F32 pdf(const ElementIntersection& ei)const override;

		virtual bool inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const override;

	protected:
		PRenderable renderable;
		F32 pdfVal;

		struct SampleData {
			VML::Vector samplePoint;
			F32 nDOTd;
		};
		std::vector<SampleData> sampleData;
	};
	PLight LoadAreaLight(std::stringstream&, World&);

	class EnvironmentLight : public Light
	{
	public:
		EnvironmentLight();

		virtual ~EnvironmentLight();

		virtual F32 getDistanceFromPoint(const VML::Vector& point)const override;
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point)override;

		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world)override;

		virtual F32 pdf(const ElementIntersection& ei)const override;

		virtual bool inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const override;

	protected:
		SamplerSet samplers;
		PMaterial material;
		VML::Vector u, v, w;
		VML::Vector wi;
	};
	PLight LoadEnvironmentLight(std::stringstream&, World&);
}