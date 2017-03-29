#pragma once

#include <AssetManager.h>
#include <Renderable.h>
#include <AmbientLights.h>
#include <Camera.h>

namespace RT
{
	// Output of a ray trace intersection
	struct ElementIntersection
	{
		ElementIntersection() : bHit(false) { }

		bool bHit;
		Renderable element;
		RayIntersection rayInt;
		Ray ray;
	};


	class World
	{
	public:
		// Constructor.
		World();
		virtual ~World() = default;

		void loadFromFile(const std::string& file);

		void addRenderable(PRenderable r);
		Renderables& getRenderables();

		void addLight(PLight light);
		Lights& getLights();

		void setCamera(PCamera camera);
		PCamera getCamera();

		bool traceRayColor(Color& out, const Ray& ray);

		void traceRayIntersections(ElementIntersection& out, const Ray& ray)const;
		void traceRayIntersections(bool& bHit, F32 d, const Ray& ray)const;

	public:
		AssetManager assetManager;
		PAmbientLight ambient;

	private:
		PCamera camera;

		Renderables renderables;
		Lights lights;
	};

}