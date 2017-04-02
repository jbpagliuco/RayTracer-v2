#pragma once

#include <Light.h>
#include <Color.h>

namespace RT
{
	class AmbientLight : public Light
	{
	public:
		AmbientLight();
		// @param ls - The multiplicative factor.
		// @param color - The color of this light.
		AmbientLight(F32 ls, Color color);

		virtual ~AmbientLight();

		virtual F32 getDistanceFromPoint(const VML::Vector& point)const override;
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point)override;

		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world)override;

		virtual bool inShadow(const Ray& ray, const ElementIntersection& ei, const World& world)const override;

	protected:
		Color color;
		F32 ls;
	};
	typedef std::shared_ptr<AmbientLight> PAmbientLight;
	PLight LoadAmbientLight(std::stringstream&, World&);

	class AmbientOccluder : public AmbientLight
	{
	public:
		AmbientOccluder();
		// @param ls - The multiplicative factor.
		// @param color - The color of this light.
		AmbientOccluder(F32 ls, Color color, F32 minAmount);

		virtual ~AmbientOccluder();

		virtual F32 getDistanceFromPoint(const VML::Vector& point)const override;
		virtual VML::Vector getDirectionFromPoint(const VML::Vector& point)override;

		virtual Color calculateRadiance(const ElementIntersection& ei, const World& world)override;

	private:
		virtual VML::Vector sampleDirection();

	private:
		VML::Vector u, v, w;
		SamplerSet sampler;
		F32 minAmount;
	};
	PLight LoadAmbientOccluderLight(std::stringstream&, World&);
}