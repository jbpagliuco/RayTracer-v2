#include <Noise.h>

namespace RT
{
	CubicNoise::CubicNoise() {}

	CubicNoise::CubicNoise(I32 octaves) : LatticeNoise(octaves) {}

	CubicNoise::CubicNoise(I32 octaves, F32 lacunarity, F32 gain) : LatticeNoise(octaves, lacunarity, gain) {}

	CubicNoise::~CubicNoise()
	{

	}

	F32 CubicNoise::valueNoise(const VML::Vector& point)const
	{
		Vector3i i;
		Vector3f f;
		F32 xknots[4], yknots[4], zknots[4];

		VML::VECTOR3F p = point.asVector3();

		for (I32 j = 0; j < 3; j++)
		{
			i.v[j] = floor(p.v[j]);
			f.v[j] = p.v[j] - i.v[j];
		}

		for (I32 k = -1; k <= 2; k++) {
			for (I32 j = -1; j <= 2; j++) {
				for (I32 ii = -1; ii <= 2; ii++) {
					xknots[ii + 1] = valueTable[INDEX(i.x + ii, i.y + j, i.z + k)];
				}
				yknots[j + 1] = FourKnotSpline(f.x, xknots);
			}
			zknots[k + 1] = FourKnotSpline(f.y, yknots);
		}

		return Clamp(FourKnotSpline(f.z, zknots), -1.0f, 1.0f);
	}
}