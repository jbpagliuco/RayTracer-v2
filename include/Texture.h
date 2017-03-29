#pragma once

#include <Util.h>
#include <ImageCV.h>
#include <map>

namespace RT
{
	// Forward declaration
	class World;

	class Texture2D
	{
	public:
		Texture2D();

		virtual ~Texture2D();

		virtual Color getColor(F32 u, F32 v)const = 0;
	};
	typedef std::shared_ptr<Texture2D> PTexture2D;

	class ImageTexture2D : public Texture2D
	{
	public:
		ImageTexture2D(const std::string& filename);

		virtual ~ImageTexture2D();

		virtual Color getColor(F32 u, F32 v)const override;

	protected:
		ImageCV image;
	};
	PTexture2D LoadImageTexture2D(std::stringstream&, World&);
	
	PTexture2D LoadTexture2D(const std::map<std::string, std::string>& params, World&);
	PTexture2D LoadTexture2D(const std::string& params, World&);
}