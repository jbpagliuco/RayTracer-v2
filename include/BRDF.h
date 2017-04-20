#pragma once

#include <Sampler.h>
#include <Color.h>

namespace RT
{
	// Forward declaration
	struct ElementIntersection;

	class BRDF
	{
	public:
		BRDF();

		virtual ~BRDF();

		// Calculates the BRDF.
		// @param ei - The intersection.
		// @param wi - The incoming direction.
		// @param wo - The outgoing direction.
		virtual Color f(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const;

		// Samples the BRDF.
		// @param ei - The intersection.
		// @param wi - The incoming direction.
		// @param wo - The outgoing direction.
		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wi, const VML::Vector& wo);

		// Calculates the bihemispherical reflectance.
		// @param ei - The intersection.
		// @param wi - The incoming direction.
		// @param wo - The outgoing direction.
		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wi, const VML::Vector& wo)const;

		// Calculates the bihemispherical reflectance.
		// @param ei - The intersection.
		// @param wo - The outgoing direction.
		virtual Color rho(const ElementIntersection& ei, const VML::Vector& wo)const;
	};
}