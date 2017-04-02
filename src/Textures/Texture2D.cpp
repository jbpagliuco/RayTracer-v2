#include <Texture.h>
#include <sstream>
#include <World.h>

namespace RT
{
	Texture2D::Texture2D() {}

	Texture2D::~Texture2D() {}


	ImageTexture2D::ImageTexture2D(const std::string& filename) : image(filename) {}

	ImageTexture2D::~ImageTexture2D() {}

	Color ImageTexture2D::getColor(F32 u, F32 v)const
	{
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





	typedef PTexture2D(*Texture2DLoader)(std::stringstream&, World&);
	std::map<std::string, Texture2DLoader> loaders = {
		{ "image", LoadImageTexture2D }
	};

	PTexture2D LoadTexture2D(const std::map<std::string, std::string>& params, World& world)
	{
		std::string type = params.at("type");
		std::stringstream ss(params.at("params"));

		return loaders[type](ss, world);
	}

	PTexture2D LoadTexture2D(const std::string& params, World& world)
	{
		std::stringstream ss(params);

		std::map<std::string, std::string> p;
		ss >> p["type"];

		std::string curr;
		while (!(ss >> curr).eof())
			p["params"] += curr + " ";
		p["params"] += curr;

		return LoadTexture2D(p, world);
	}
}