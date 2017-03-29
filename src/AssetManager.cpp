#include <AssetManager.h>
#include <P4Mem.h>
#include <assert.h>

namespace RT
{
	AssetManager::AssetManager()
	{
	}

	AssetManager::~AssetManager()
	{
	}


	void AssetManager::AddGeometry(PGeometry pGeo)
	{
		geometry.unnamed.push_back(pGeo);
	}

	void AssetManager::AddGeometry(const std::string& name, PGeometry pGeo)
	{
		if (!pGeo)
			return;

		geometry.named[name] = pGeo;
	}

	PGeometry AssetManager::GetGeometry(const std::string& name)const
	{
		assert(geometry.named.find(name) != geometry.named.end());

		return geometry.named.at(name);
	}

	void AssetManager::AddMaterial(PMaterial pMat)
	{
		materials.unnamed.push_back(pMat);
	}

	void AssetManager::AddMaterial(const std::string& name, PMaterial pMat)
	{
		if (!pMat)
			return;

		materials.named[name] = pMat;
	}

	PMaterial AssetManager::GetMaterial(const std::string& name)const
	{
		assert(materials.named.find(name) != materials.named.end());

		return materials.named.at(name);
	}





	void AssetManager::AddTexture2D(PTexture2D pTex)
	{
		tex2ds.unnamed.push_back(pTex);
	}

	void AssetManager::AddTexture2D(const std::string& name, PTexture2D pTex)
	{
		if (!pTex)
			return;

		tex2ds.named[name] = pTex;
	}

	PTexture2D AssetManager::GetTexture2D(const std::string& name)const
	{
		assert(tex2ds.named.find(name) != tex2ds.named.end());

		return tex2ds.named.at(name);
	}
}