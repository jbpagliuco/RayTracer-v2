#pragma once

#include <BTDF.h>
#include <World.h>

namespace RT
{
	class PerfectTransmitter : public BTDF
	{
	public:
		PerfectTransmitter(F32 kt, F32 ior);

		virtual ~PerfectTransmitter();

		virtual Color sampleF(const ElementIntersection& ei, VML::Vector& wt, const VML::Vector& wo)override;

	private:
		F32 kt;
	};
}