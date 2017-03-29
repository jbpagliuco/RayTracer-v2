#include <World.h>

#include <Log.h>
#include <RenderingEngine.h>

#include <WorldFileReader.h>

namespace RT
{
	void LoadGeometry(const std::string& name, TypeParams params, void* pWorld)
	{
		World& w = *(World*)pWorld;
		if (name != "")
		{
			PGeometry pGeo = LoadGeometry(params, w);
			w.assetManager.AddGeometry(name, pGeo);
		}
		else
		{

		}
	}

	void LoadMaterial(const std::string& name, TypeParams params, void* pWorld)
	{
		World& w = *(World*)pWorld;
		if (name != "")
		{
			PMaterial pMat = LoadMaterial(params, w);
			w.assetManager.AddMaterial(name, pMat);
		}
		else
		{

		}
	}

	void LoadTexture2D(const std::string& name, TypeParams params, void* pWorld)
	{
		World& w = *(World*)pWorld;
		if (name != "")
		{
			PTexture2D pTex = LoadTexture2D(params, w);
			w.assetManager.AddTexture2D(name, pTex);
		}
		else
		{

		}
	}

	void LoadRenderable(const std::string& name, TypeParams params, void* pWorld)
	{
		World& w = *(World*)pWorld;

		Renderable renderable(name);
		renderable.transform = LoadTransform(params["Transform"]);

		std::string geometry = params["Geometry"];
		if (geometry[0] == '@')
			renderable.geometry = w.assetManager.GetGeometry(geometry.substr(1));
		else
		{
			renderable.geometry = LoadGeometry(geometry, w);
			w.assetManager.AddGeometry(renderable.geometry);
		}

		std::string material = params["Material"];
		if (material[0] == '@')
			renderable.material = w.assetManager.GetMaterial(material.substr(1));
		else
		{
			renderable.material = LoadMaterial(material, w);
			w.assetManager.AddMaterial(renderable.material);
		}

		w.addRenderable(std::make_shared<Renderable>(renderable));
	}

	void LoadCamera(const std::string& name, TypeParams params, void* pWorld)
	{
		World& w = *(World*)pWorld;
		PCamera camera = LoadCamera(params, w);

		w.setCamera(camera);
	}

	void LoadLight(const std::string& name, TypeParams params, void* pWorld)
	{
		World& w = *(World*)pWorld;

		PLight light = LoadLight(params, w);
		w.addLight(light);
	}





	void World::loadFromFile(const std::string& file)
	{
		RT_LOG(WORLD, INIT, "Loading world from " << file);
		WorldFileReader wfr;

		wfr.AddRule("Geometry", std::vector<std::string>({ "type", "params" }), LoadGeometry);
		wfr.AddRule("Material", std::vector<std::string>({ "type", "params" }), LoadMaterial);
		wfr.AddRule("Texture2D", std::vector<std::string>({ "type", "params" }), LoadTexture2D);
		wfr.AddRule("Renderable", std::vector<std::string>({ "Transform", "Geometry", "Material" }), LoadRenderable);
		wfr.AddRule("Camera", std::vector<std::string>({ "pos", "lookat", "up", "type", "params" }), LoadCamera);
		wfr.AddRule("Light", std::vector<std::string>({ "type", "params" }), LoadLight);

		wfr.ReadFromFile(file, this);

		RT_LOG(WORLD, INIT, "Creating world grid");
		//grid.AddObjects(elements);
	}
}