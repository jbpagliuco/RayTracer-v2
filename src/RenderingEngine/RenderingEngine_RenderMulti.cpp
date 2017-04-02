#include <RenderingEngine.h>

#include <Log.h>

namespace RT
{
	std::mutex m;
	U32 numDone = 0;


	void RenderingEngine::renderScene_threadFunc(U32 idx, ThreadOutput* out, TaskQueue<ThreadData>* q)
	{
		m.lock();
		auto id = GetCurrentThreadId();
		MapThreadIndex(id, idx);
		m.unlock();

		// Each thread updates one row before updated the debug image.
		U32 step = 0;

		U32 width = camera->vp.width();
		U32 height = camera->vp.height();
		U32 numSamples = Sampler::NumSamples;

		U32 numRuns = height / NumThreads;
		out->SetMax(idx, numRuns);

		while (true)
		{
			U32 row = step * NumThreads + idx;
			if (row >= height)
				break;

			for (U32 col = 0; col < width; col++)
			{
				Color finalColor(0.0f, 0.0f, 0.0f, 1.0f);
				for (U32 s = 0; s < numSamples; s++)
				{
					Color c = camera->renderPixel(row, col, world);
					finalColor = finalColor + c;
				}

				finalColor = finalColor / numSamples;
				finalColor.Clamp();

				renderBuffer(row, col) = finalColor;
			}

			out->UpdateStep(idx, step);

			m.lock();
			ThreadData d(row, 0, row, width);
			q->Push({ row, 0, row, width });
			m.unlock();

			step++;
		}

		out->Done(idx);

		std::unique_lock<std::mutex> lock(m);
		numDone++;
		q->WriterFinish();
	}

	void RenderingEngine::renderScene_multi()
	{
		std::vector<std::thread> threads;
		ThreadOutput out;
		TaskQueue<ThreadData> q(NumThreads);

		for (U32 i = 0; i < NumThreads; i++)
			threads.push_back(std::thread(&RenderingEngine::renderScene_threadFunc, this, i, &out, &q));

		while (true)
		{
			if (q.Empty() && numDone == NumThreads)
				break;

			ThreadData e;
			bool b = q.Pop(e);
			if (!b)
				break;

			imageTracker.update(e.startRow, e.startCol, e.endRow, e.endCol);
			imageTracker.show();
		}

		for (U32 i = 0; i < NumThreads; i++)
			threads[i].join();

		std::cout << std::endl;
		system("pause");
	}
}