#include <BTDFTypes.h>

namespace RT
{
	PerfectTransmitter::PerfectTransmitter(F32 kt, F32 ior) : kt(kt), BTDF(ior)
	{

	}

	PerfectTransmitter::~PerfectTransmitter()
	{

	}

	Color PerfectTransmitter::sampleF(const ElementIntersection& ei, VML::Vector& wt, const VML::Vector& wo)
	{
		VML::Vector n = ei.rayInt.normal;
		F32 cThetai = n.v3Dot(wo);
		F32 eta = ior;

		if (cThetai < 0.0f)
		{
			cThetai = -cThetai;
			n.negate();
			eta = 1.0f / eta;
		}

		F32 temp = 1.0f - (1.0f - cThetai*cThetai) / (eta*eta);
		F32 cTheta2 = sqrt(temp);

		VML::Vector nWo = VML::Vector(wo).negate();
		wt = nWo / eta - n * (cTheta2 - cThetai / eta);

		const Color white(1.0f, 1.0f, 1.0f, 1.0f);
		return (white / n.v3Dot(wt)) * (kt / (eta*eta));
	}
}