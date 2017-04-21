#pragma once

#include <Texture.h>
#include <World.h>
#include <Noise.h>

namespace RT
{
	class ImageTexture2D : public Texture2D
	{
	public:
		ImageTexture2D(const std::string& filename);

		virtual ~ImageTexture2D();

		virtual Color getColor(const ElementIntersection& ei)const override;

	protected:
		ImageCV image;
	};
	PTexture2D LoadImageTexture2D(std::stringstream&, World&);

	class FBMTexture2D : public Texture2D
	{
	public:
		FBMTexture2D(PLatticeNoise noise, Color color, F32 min, F32 max);

		virtual ~FBMTexture2D();

		virtual Color getColor(const ElementIntersection& ei)const override;

	protected:
		PLatticeNoise noise;
		Color color;
		F32 minValue, maxValue;
	};
	PTexture2D LoadFBMTexture2D(std::stringstream&, World&);

	class WrappedFBMTexture2D : public Texture2D
	{
	public:
		WrappedFBMTexture2D(PLatticeNoise noise, Color color, F32 expansionNumber);

		virtual ~WrappedFBMTexture2D();

		virtual Color getColor(const ElementIntersection& ei)const override;

	protected:
		PLatticeNoise noise;
		Color color;
		F32 expansionNumber;
	};
	PTexture2D LoadWrappedFBMTexture2D(std::stringstream&, World&);
}