#include <TextureTypes.h>

namespace RT
{
	FBMTexture2D::FBMTexture2D(PLatticeNoise noise, Color color, F32 min, F32 max)
		: noise(noise), color(color), minValue(min), maxValue(max) 
	{}

	FBMTexture2D::~FBMTexture2D() {}

	Color FBMTexture2D::getColor(const ElementIntersection& ei)const
	{
		F32 value = noise->valueFBM(ei.rayInt.worldCoords);
		value = minValue + (maxValue - minValue) * value;

		return color * value;
	}


	PTexture2D LoadFBMTexture2D(std::stringstream& ss, World& world)
	{
		std::string noiseType;
		I32 numOctaves;
		F32 gain, lacunarity;
		Color color;
		F32 min, max;
		ss >> noiseType >> numOctaves >> lacunarity >> gain
			>> color.r >> color.g >> color.b
			>> min >> max;

		std::map<std::string, PLatticeNoise> noiseConv = {
			{ "cubic", std::make_shared<CubicNoise>(numOctaves, lacunarity, gain) }
		};

		return AllocateAligned16(FBMTexture2D(noiseConv[noiseType], color, min, max));
	}
}