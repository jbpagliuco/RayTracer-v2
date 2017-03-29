#pragma once

#include <Util.h>
#include <Buffer.h>

#include <opencv2/highgui.hpp>

namespace RT
{
	class ImageCV
	{
	public:
		ImageCV();
		// Creates an empty image.
		// @param width - The width of the image.
		// @param height - The height of the image.
		ImageCV(U32 width, U32 height);

		// Creates an image and initializes it to the buffer.
		// @param width - The width of the image.
		// @param height - The height of the image.
		// @param colorBuffer - The color buffer.
		ImageCV(U32 width, U32 height, const ColorBuffer2D* colorBuffer);

		ImageCV(const std::string& filename);

		virtual ~ImageCV() = default;

		virtual Color getColor(U32 row, U32 col)const;

		U32 width()const;
		U32 height()const;

		// Saves this image to a file on disk.
		// @param file - The filename.
		void saveToFile(const std::string& file)const;

	private:
		cv::Mat img;
	};


	
	// Tracks an image buffer and displays it to a window
	class ImageTracker
	{
	public:
		ImageTracker();
		virtual ~ImageTracker();

		void setBuffer(ColorBuffer2D * pBuffer);

		void update(U32 row, U32 col);
		void update(U32 startRow, U32 startCol, U32 endRow, U32 endCol);
		void show();

	private:
		cv::Mat img;
		ColorBuffer2D * buffer;

		U32 lastIndex;
	};
}