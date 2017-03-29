#pragma once

#include <Geometry.h>
#include <Material.h>
#include <Texture.h>
#include <map>

namespace RT
{
	class AssetManager
	{
	public:
		AssetManager();

		virtual ~AssetManager();

		void AddGeometry(PGeometry pGeo);
		void AddGeometry(const std::string& name, PGeometry pGeo);
		PGeometry GetGeometry(const std::string& name)const;

		void AddMaterial(PMaterial pMat);
		void AddMaterial(const std::string& name, PMaterial pMat);
		PMaterial GetMaterial(const std::string& name)const;

		void AddTexture2D(PTexture2D pTex);
		void AddTexture2D(const std::string& name, PTexture2D pTex);
		PTexture2D GetTexture2D(const std::string& name)const;

	private:
		template <typename T>
		struct AssetContainer
		{
			AssetContainer() {}
			std::vector<T> unnamed;
			std::map<std::string, T> named;
		};
		
		AssetContainer<PGeometry> geometry;
		AssetContainer<PMaterial> materials;
		AssetContainer<PTexture2D> tex2ds;
	};
}