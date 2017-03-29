#include <Camera.h>

#include <assert.h>

namespace RT
{
	Viewport::Viewport(U32 width, U32 height)
	{
		this->w = width;
		this->h = height;
		this->pixelWidth = 2.0f / (F32)width;
	}

	VML::VECTOR3F Viewport::getPixelCenter(U32 row, U32 col)const
	{
		assert(row >= 0 && row < h && col >= 0 && col < w);

		VML::VECTOR3F p;
		p.x = pixelWidth * (col - (w / 2.0f) + 0.5f);
		p.y = -pixelWidth * (row - (h / 2.0f) + 0.5f);
		p.z = 0.0f;

		return p;
	}

	VML::VECTOR3F Viewport::getUnitSquareSample(U32 row, U32 col)
	{
		assert(row >= 0 && row < h && col >= 0 && col < w);

		VML::VECTOR2F sp = sampler.sampleUnitSquare();

		VML::VECTOR3F p;
		p.x = pixelWidth * (col - (w / 2.0f) + sp.x);
		p.y = -pixelWidth * (row - (h / 2.0f) + sp.y);
		p.z = 0.0f;

		return p;
	}


	Sampler * Viewport::getSampler()
	{
		return &sampler;
	}


	U32 Viewport::width()const
	{
		return w;
	}

	U32 Viewport::height()const
	{
		return h;
	}


	void Viewport::scalePixelWidth(F32 scale)
	{
		pixelWidth /= scale;
	}
}