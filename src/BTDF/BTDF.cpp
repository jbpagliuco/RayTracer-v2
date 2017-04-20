#pragma once

#include <BTDF.h>
#include <World.h>

namespace RT
{
	BTDF::BTDF(F32 ior) : ior(ior)
	{
	}

	BTDF::~BTDF()
	{
	}


	Color BTDF::f(const ElementIntersection& ei, const VML::Vector& wt, const VML::Vector& wo)const
	{
		return Color();
	}

	Color BTDF::sampleF(const ElementIntersection& ei, VML::Vector& wt, const VML::Vector& wo)
	{
		return Color();
	}

	Color BTDF::rho(const ElementIntersection& ei, const VML::Vector& wt, const VML::Vector& wo)const
	{
		return Color();
	}

	Color BTDF::rho(const ElementIntersection& ei, const VML::Vector& wo)const
	{
		return Color();
	}

	bool BTDF::tir(const ElementIntersection& ei)const
	{
		VML::Vector wo = ei.ray.direction();
		wo.negate();
		
		F32 cThetai = ei.rayInt.normal.v3Dot(wo);
		F32 eta = ior;

		if (cThetai < 0.0f)
			eta = 1.0f / eta;

		return (1.0f - (1.0f - cThetai*cThetai) / (eta*eta)) < 0.0f;
	}
}