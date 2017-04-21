#include <TextureTypes.h>

namespace RT
{
	WrappedFBMTexture2D::WrappedFBMTexture2D(PLatticeNoise noise, Color color, F32 expansionNumber)
		: noise(noise), color(color), expansionNumber(expansionNumber)
	{}

	WrappedFBMTexture2D::~WrappedFBMTexture2D() {}

	Color WrappedFBMTexture2D::getColor(const ElementIntersection& ei)const
	{
		F32 noiseValue = expansionNumber * noise->valueFBM(ei.rayInt.worldCoords);
		F32 value = noiseValue - floor(noiseValue);

		return color * value;
	}


	PTexture2D LoadWrappedFBMTexture2D(std::stringstream& ss, World& world)
	{
		std::string noiseType;
		I32 numOctaves;
		F32 gain, lacunarity;
		Color color;
		F32 expansionNumber;

		ss >> noiseType >> numOctaves >> lacunarity >> gain
			>> color.r >> color.g >> color.b
			>> expansionNumber;

		std::map<std::string, PLatticeNoise> noiseConv = {
			{ "cubic", std::make_shared<CubicNoise>(numOctaves, lacunarity, gain) }
		};

		return AllocateAligned16(WrappedFBMTexture2D(noiseConv[noiseType], color, expansionNumber));
	}
}