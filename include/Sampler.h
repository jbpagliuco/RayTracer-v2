#pragma once

#include <Util.h>
#include <VML.h>

namespace RT
{
	// Generates a sample of points.
	typedef std::vector<VML::VECTOR2F>(*SamplerGenerator)(I32, I32);


	class Sampler
	{
	public:
		static I32 NumSamples;
		static SamplerGenerator Generator;

	public:
		// Default constructor
		Sampler();

		// Destructor
		virtual ~Sampler();

		// Get the next sample on the unit square.
		VML::VECTOR2F sampleUnitSquare();

		void mapSamplesToHemisphere(F32 p);
		VML::VECTOR3F sampleHemisphere();

	private:
		// Sets up the shuffled sampling indices
		void setupShuffledIndices();

	private:
		// Number of sample sets
		I32 numSets;

		// Sample points on a unit square
		std::vector<VML::VECTOR2F> samples;
		// Shuffled samples array indices
		std::vector<I32> shuffledIndices;

		// Sample points on a unit hemisphere
		std::vector<VML::VECTOR3F> samplesHemi;

		// The current number of sample points used
		U32 count;
		// Random jump index
		I32 jump;
	};
	typedef std::shared_ptr<Sampler> PSampler;


	class SamplerSet
	{
	public:
		SamplerSet();

		virtual ~SamplerSet();

		// Get the next sample on the unit square.
		VML::VECTOR2F sampleUnitSquare();

		void mapSamplesToHemisphere(F32 p);
		VML::VECTOR3F sampleHemisphere();

		PSampler get();

	private:
		std::vector<PSampler> samplers;
	};


	// Generates sample points from a regular distribution.
	std::vector<VML::VECTOR2F> RegularSampler(I32 numSamples, I32 numSets);
	// Generates sample points from a multi-jittered distribution.
	std::vector<VML::VECTOR2F> MultiJitteredSampler(I32 numSamples, I32 numSets);

	// Returns a sample generator from the string.
	SamplerGenerator GetSamplerGeneratorFromString(const std::string& str);
}