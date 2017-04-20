#pragma once

#include <Color.h>
#include <VML.h>

namespace RT
{
	// Forward declaration
	struct ElementIntersection;

	class BTDF
	{
	public:
		BTDF(F32 ior);

		virtual ~BTDF();

		// Calculates the BRDF.
		// @param ei - The intersection.
		// @param wi - The incoming direction.
		// @param wo - The outgoing direction.
		virtual Color f(const ElementIntersection& ei, const VML::Vector& wt, const VML::Vector& wo)const;

		// Samples the BRDF.
		// @param ei - The intersection.
		// @param wi - The incoming direction.
		// @param wo - The outgoing direction.
		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wt, const VML::Vector& wo);

		// Calculates the bihemispherical reflectance.
		// @param ei - The intersection.
		// @param wi - The incoming direction.
		// @param wo - The outgoing direction.
		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wt, const VML::Vector& wo)const;

		// Calculates the bihemispherical reflectance.
		// @param ei - The intersection.
		// @param wo - The outgoing direction.
		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wo)const;

		virtual bool tir(const ElementIntersection& ei)const;

	protected:
		F32 ior;
	};
}