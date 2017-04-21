#pragma once

#include <Util.h>
#include <VML.h>

#define PERM(x)          permutationTable[(x)&kTableMask]
#define INDEX(ix,iy,iz)  PERM((ix)+PERM((iy)+PERM(iz)))

namespace RT
{
	const I32 kTableSize = 256;
	const I32 kTableMask = kTableSize - 1;
	const I32 seedValue = 253;

	class LatticeNoise
	{
	public:
		LatticeNoise();
		LatticeNoise(I32 octaves);
		LatticeNoise(I32 octaves, F32 lacunarity, F32 gain);

		virtual ~LatticeNoise();

		virtual F32 valueNoise(const VML::Vector& point)const = 0;
		virtual F32 valueFractalSum(const VML::Vector& point)const;
		virtual F32 valueTurbulence(const VML::Vector& point)const;
		virtual F32 valueFBM(const VML::Vector& point)const;

	protected:
		static const byte permutationTable[kTableSize];
		F32 valueTable[kTableSize];
		VML::VECTOR3F vectorTable[kTableSize];

		I32 numOctaves;
		F32 lacunarity, gain;
		F32 fbmMin, fbmMax;

	private:
		void initValueTable(I32 seed);
		void initVectorTable(I32 seed);
		void computeFBMBounds();
	};
	typedef std::shared_ptr<LatticeNoise> PLatticeNoise;


	class LinearNoise : public LatticeNoise
	{
	public:
		LinearNoise();
		LinearNoise(I32 octaves);
		LinearNoise(I32 octaves, F32 lacunarity, F32 gain);

		virtual ~LinearNoise();

		virtual F32 valueNoise(const VML::Vector& point)const override;
	};

	class CubicNoise : public LatticeNoise
	{
	public:
		CubicNoise();
		CubicNoise(I32 octaves);
		CubicNoise(I32 octaves, F32 lacunarity, F32 gain);

		virtual ~CubicNoise();

		virtual F32 valueNoise(const VML::Vector& point)const override;
	};
}