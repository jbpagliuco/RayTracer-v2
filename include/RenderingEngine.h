#pragma once

#include <string>
#include <World.h>
#include <Camera.h>
#include <ThreadUtil.h>

namespace RT
{
	class RenderingEngine
	{
	public:
		static U32 NumThreads;

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
		void renderScene_single();
		void renderScene_multi();

		struct ThreadData
		{
			ThreadData() {}
			ThreadData(U32 startRow, U32 startCol, U32 endRow, U32 endCol) :
				startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol) {}

			U32 startRow, startCol;
			U32 endRow, endCol;
		};
		void renderScene_threadFunc(U32 idx, ThreadOutput* out, TaskQueue<ThreadData>* q);

	private:
		ColorBuffer2D renderBuffer;
		ImageTracker imageTracker;

		PCamera camera;
		Color bkgColor;
		Viewport vp;

		World world;

		bool bUseMultiThreading;

		std::string outputFolder;
		std::string outputFilename;
	};
}