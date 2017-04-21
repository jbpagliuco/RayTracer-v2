#include <TextureTypes.h>
#include <sstream>

namespace RT
{
	Texture2D::Texture2D() {}

	Texture2D::~Texture2D() {}

	typedef PTexture2D(*Texture2DLoader)(std::stringstream&, World&);
	std::map<std::string, Texture2DLoader> loaders = {
		{ "image", LoadImageTexture2D },
		{ "fbm", LoadFBMTexture2D },
		{ "wrappedfbm", LoadWrappedFBMTexture2D }
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