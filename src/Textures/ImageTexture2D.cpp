#include <TextureTypes.h>

namespace RT
{
	ImageTexture2D::ImageTexture2D(const std::string& filename) : image(filename) {}

	ImageTexture2D::~ImageTexture2D() {}

	Color ImageTexture2D::getColor(const ElementIntersection& ei)const
	{
		F32 u = ei.rayInt.uv.x;
		F32 v = ei.rayInt.uv.y;

		u = Clamp(u, 0.0f, 1.0f);
		v = Clamp(v, 0.0f, 1.0f);
		return image.getColor((U32)(v * (image.height() - 1)), (U32)(u * (image.width() - 1)));
	}


	PTexture2D LoadImageTexture2D(std::stringstream& ss, World& world)
	{
		std::string filename;
		ss >> filename;

		return AllocateAligned16(ImageTexture2D(filename));
	}
}