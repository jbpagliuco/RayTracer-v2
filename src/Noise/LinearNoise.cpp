#include <Noise.h>

namespace RT
{
	LinearNoise::LinearNoise() {}

	LinearNoise::LinearNoise(I32 octaves) : LatticeNoise(octaves) {}

	LinearNoise::LinearNoise(I32 octaves, F32 lacunarity, F32 gain) : LatticeNoise(octaves, lacunarity, gain) {}

	LinearNoise::~LinearNoise()
	{

	}

	F32 LinearNoise::valueNoise(const VML::Vector& point)const
	{
		Vector3i i;
		Vector3f f;
		F32 d[2][2][2];
		F32 x0, x1, x2, x3, y0, y1, z0;

		VML::VECTOR3F p = point.asVector3();

		for (I32 j = 0; j < 3; j++)
		{
			i.v[j] = floor(p.v[j]);
			f.v[j] = p.v[j] - i.v[j];
		}

		for (I32 k = 0; k <= 1; k++)
			for (I32 j = 0; j <= 1; j++)
				for (I32 ii = 0; ii <= 1; ii++)
					d[k][j][ii] = valueTable[INDEX(i.x + ii, i.y + j, i.z + k)];

		x0 = Lerp(f.x, d[0][0][0], d[0][0][1]);
		x1 = Lerp(f.x, d[0][1][0], d[0][1][1]);
		x2 = Lerp(f.x, d[1][0][0], d[1][0][1]);
		x3 = Lerp(f.x, d[1][1][0], d[1][1][1]);
		y0 = Lerp(f.y, x0, x1);
		y1 = Lerp(f.y, x2, x3);
		z0 = Lerp(f.z, y0, y1);

		return z0;
	}
}