#pragma once

#include <string>
#include <World.h>
#include <Camera.h>

namespace RT
{
	class RenderingEngine
	{
	public:
		// Initializes the rendering engine and loads any necessary components.
		// @param configFile - The filename of the configuration file to read from.
		RenderingEngine(const std::string& configFile);

		// Default destructor.
		virtual ~RenderingEngine() = default;

		// Run the ray tracer on the world.
		void render();

	private:
		void renderScene();

	private:
		ColorBuffer2D renderBuffer;
		ImageTracker imageTracker;

		PCamera camera;
		Color bkgColor;
		Viewport vp;

		World world;

		std::string outputFolder;
		std::string outputFilename;
	};
}