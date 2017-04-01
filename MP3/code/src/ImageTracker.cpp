#include <ImageCV.h>

#define WINDOW_NAME "DEBUG DISPLAY"

namespace RT
{
	ImageTracker::ImageTracker()
	{
		buffer = nullptr;
		lastIndex = 0;

		cv::namedWindow(WINDOW_NAME);
	}

	ImageTracker::~ImageTracker()
	{
		cv::destroyWindow(WINDOW_NAME);
	}

	void ImageTracker::setBuffer(ColorBuffer2D * pBuffer)
	{
		buffer = pBuffer;

		img = cv::Mat(buffer->GetHeight(), buffer->GetWidth(), CV_8UC4, cv::Scalar(0, 0, 0, 255));
	}


	void ImageTracker::update(U32 startRow, U32 startCol, U32 endRow, U32 endCol)
	{
		assert(buffer);

		U32 width = buffer->GetWidth();
		I32 startIndex = startRow * width + startCol;
		I32 endIndex = endRow * width + endCol;
		for (I32 i = startIndex; i < endIndex; i++)
		{
			ColorU8 cu8 = buffer->operator()(i).ToColorU8();
			cv::Vec4b v(cu8.b, cu8.g, cu8.r, cu8.a);

			U32 r = i / width;
			U32 c = i % width;
			img.at<cv::Vec4b>(cv::Point(c, r)) = v;
		}
	}


	void ImageTracker::update(U32 row, U32 col)
	{
		assert(buffer);

		U32 width = buffer->GetWidth();
		I32 newIndex = row * width + col;
		for (I32 i = lastIndex; i <= newIndex; i++)
		{
			ColorU8 cu8 = buffer->operator()(i).ToColorU8();
			cv::Vec4b v(cu8.b, cu8.g, cu8.r, cu8.a);

			U32 r = i / width;
			U32 c = i % width;
			img.at<cv::Vec4b>(cv::Point(c, r)) = v;
		}
		lastIndex = newIndex;

		cv::imshow(WINDOW_NAME, img);
		cv::waitKey(1);
	}






	void ImageTracker::show()
	{
		cv::imshow(WINDOW_NAME, img);
		cv::waitKey(1);
	}
}