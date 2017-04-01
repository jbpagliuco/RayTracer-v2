#pragma once

#include <AssetManager.h>
#include <Renderable.h>
#include <AmbientLights.h>
#include <Camera.h>
#include <AccelerationStructure.h>

namespace RT
{
	class WorldASData : public ASData
	{
	public:
		WorldASData(PRenderable& r);
		virtual ~WorldASData() = default;

		virtual PGeometry geometry()const override;
		virtual BoundingBox bbox()const override;
		virtual Transform transform()const override;

	public:
		PRenderable r;
	};


	class World
	{
	public:
		// Constructor.
		World();
		virtual ~World() = default;

		void loadFromFile(const std::string& file);

		void addRenderable(PRenderable r);
		std::map<std::string, PRenderable>& getRenderables();

		void addLight(PLight light);
		Lights& getLights();

		void setCamera(PCamera camera);
		PCamera getCamera();

		Color traceRayColor(const Ray& ray, I32 depth = 0);

		void traceRayIntersections(ElementIntersection& out, const Ray& ray)const;
		void traceRayIntersections(bool& bHit, F32 d, const Ray& ray)const;

	public:
		AssetManager assetManager;
		PAmbientLight ambient;

	private:
		PCamera camera;

		std::map<std::string, PRenderable> renderables;
		std::unique_ptr<AccelerationStructure> acc;
		Lights lights;
	};

}