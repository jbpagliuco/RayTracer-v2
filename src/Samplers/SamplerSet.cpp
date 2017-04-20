#include <Sampler.h>

#include <ThreadUtil.h>
#include <RenderingEngine.h>

namespace RT
{
	SamplerSet::SamplerSet()
	{
		for (U32 i = 0; i < RenderingEngine::NumThreads; i++)
			samplers.push_back(std::make_shared<Sampler>());
	}

	SamplerSet::~SamplerSet()
	{

	}

	VML::VECTOR2F SamplerSet::sampleUnitSquare()
	{
		return samplers[GetThreadIndex()]->sampleUnitSquare();
	}

	void SamplerSet::mapSamplesToHemisphere(F32 p)
	{
		for (I32 i = 0; i < samplers.size(); i++)
			samplers[i]->mapSamplesToHemisphere(p);
	}

	VML::VECTOR3F SamplerSet::sampleHemisphere()
	{
		return samplers[GetThreadIndex()]->sampleHemisphere();
	}

	PSampler SamplerSet::get()
	{
		return samplers[GetThreadIndex()];
	}
}