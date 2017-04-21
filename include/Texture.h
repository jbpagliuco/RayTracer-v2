#pragma once

#include <Util.h>
#include <ImageCV.h>
#include <map>

namespace RT
{
	// Forward declaration
	class World;
	struct ElementIntersection;

	class Texture2D
	{
	public:
		Texture2D();

		virtual ~Texture2D();

		virtual Color getColor(const ElementIntersection& ei)const = 0;
	};
	typedef std::shared_ptr<Texture2D> PTexture2D;
	
	PTexture2D LoadTexture2D(const std::map<std::string, std::string>& params, World&);
	PTexture2D LoadTexture2D(const std::string& params, World&);
}