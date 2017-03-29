#include <RenderingEngine.h>

#include <Log.h>
#include <P4ConfigReader.h>
#include <direct.h>

namespace RT
{
	RenderingEngine::RenderingEngine(const std::string& configFile)
	{
		RT_LOG(RENDER_ENG, INIT, "Initializing rendering engine");
		P4::ConfigReader::Reader config;

		std::string worldFile;
		config.addSetting("world_file", &worldFile, P4_CR_STRING);

		U32 resX, resY;
		config.addSetting("res_x", &resX, P4_CR_U32);
		config.addSetting("res_y", &resY, P4_CR_U32);
		config.addSetting("bkg_color", &bkgColor, LoadColorFromConfigFile);
		config.addSetting("output_folder", &outputFolder, P4_CR_STRING);
		config.addSetting("output_name", &outputFilename, P4_CR_STRING);

		std::string vpSamplerType;
		config.addSetting("num_samples", &Sampler::NumSamples, P4_CR_I32);
		config.addSetting("viewport_sampler_type", &vpSamplerType, P4_CR_STRING);

		config.importSettings(configFile);

		Sampler::Generator = GetSamplerGeneratorFromString(vpSamplerType);

		RT_LOG(RENDER_ENG, INIT, "Num Samples: " << Sampler::NumSamples);

		// Create viewport
		vp = Viewport(resX, resY);

		// Create render target buffer
		renderBuffer = ColorBuffer2D(vp.width(), vp.height(), true);
		imageTracker.setBuffer(&renderBuffer);

		world.loadFromFile(worldFile);
		
		camera = world.getCamera();
		camera->setViewport(vp);
		camera->setBackgroundColor(bkgColor);
	}

	void RenderingEngine::render()
	{
		RT_LOG(ENGINE, RUNTIME, "Rendering scene");
		// Start time
		auto start = GetTime();

		// Run ray tracer
		renderScene();

		// Total running time for the ray tracer
		U64 elapsedTime = DiffTime(start, GetTime());
		D64 elapsedSeconds = ((D64)elapsedTime / 1000000.0);
		D64 elapsedMinutes = elapsedSeconds / 60.0;

		// Viewport stats
		U32 width = camera->getViewport().width();
		U32 height = camera->getViewport().height();
		U32 numSamples = Sampler::NumSamples;

		// Other stats
		U64 numWorldElements = world.getRenderables().size();
		U64 numPrimaryRays = numSamples * width * height;
		U64 numLights = world.getLights().size();

		D64 averageTPP = (D64)elapsedTime / ((D64)width * (D64)height);

		std::stringstream ss;
		ss <<
			"------------------------------------------------------------" <<
			"\nElapsed Time: " << elapsedTime << " usec (" << elapsedSeconds << " sec) (" << elapsedMinutes << " min)" <<
			"\nNumber of objects in world: " << numWorldElements <<
			"\nNumber of lights in world: " << numLights <<
			"\nNumber of samples per pixel: " << numSamples <<
			"\nNumber of primary rays shot: " << numPrimaryRays <<
			"\nRender target stats: " <<
			"\n\tResolution: " << width << "x" << height <<
			"\n\tTotal number of pixels rendered: " << width * height <<
			"\n\tAverage time per pixel: " << averageTPP << " usec" <<
			"\n\tAverage time per pixel per sample: " << averageTPP / numSamples << " usec" <<
			"\n------------------------------------------------------------";

		// Dump stats to console
		std::string stats = ss.str();
		RT_LOG(RENDER_ENG, RUNTIME, "RENDER STATS\n" << stats);


		// Dump results to file
		outputFolder = "Output/" + outputFolder;
		_mkdir(outputFolder.c_str());

		std::stringstream outputFileSS;
		if (outputFolder != "")
			outputFolder += "/";

		if (outputFilename != "")
			outputFileSS << outputFolder << outputFilename;
		else
		{
			outputFileSS << outputFolder << "result-" <<
				width << "x" << height << "-" <<
				numSamples << "SAMPLES" <<
				".png";
		}

		RT_LOG(RENDER_ENG, RUNTIME, "Writing result image to " << outputFileSS.str());

		renderBuffer.saveToImage(outputFileSS.str());

		outputFileSS << ".stats";
		RT_LOG(RENDER_ENG, RUNTIME, "Writing result stats to " << outputFileSS.str());
		std::ofstream out(outputFileSS.str());
		out << ss.str();
		out.close();
	}
}