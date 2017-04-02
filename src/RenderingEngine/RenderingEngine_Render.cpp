#include <RenderingEngine.h>

#include <Log.h>
#include <ThreadUtil.h>

namespace RT
{
	void RenderingEngine::renderScene_single()
	{
		MapThreadIndex(GetCurrentThreadId(), 0);

		U32 width = vp.width();
		U32 height = vp.height();
		U32 numSamples = Sampler::NumSamples;

		U32 pixelIndex = 0;
		U32 totalNumPixels = vp.width() * vp.height();
		U32 updateFreq = 800 / numSamples;

		auto start = GetTime();

		for (U32 row = 0; row < height; row++)
		{
			for (U32 col = 0; col < width; col++)
			{
				if (pixelIndex % updateFreq == 0)
				{
					imageTracker.update(row, col);
					F32 percent = (F32)pixelIndex / (F32)totalNumPixels * 100.0f;

					auto elapsed = DiffTime(start, GetTime());
					D64 total = 100.0 * elapsed / percent;

					RT_LOG_SAMELINE(RENDER_ENG, RUNTIME, "Progress: " << percent << "% ("
						<< "E: " << (elapsed / 1000000. / 60.)
						<< ", R: " << ((total - elapsed) / 1000000. / 60.) << ")");

				}

				pixelIndex++;

				Color finalColor(0.0f, 0.0f, 0.0f, 1.0f);
				for (U32 s = 0; s < numSamples; s++)
				{
					Color c = camera->renderPixel(row, col, world);

					finalColor = finalColor + c;
				}

				finalColor = finalColor / (F32)numSamples;
				finalColor.Clamp();

				renderBuffer(row, col) = finalColor;
			}
		}

		RT_LOG_NEWLINE();

		imageTracker.update(vp.height() - 1, vp.width() - 1);
	}
}