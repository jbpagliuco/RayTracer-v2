#include <Buffer.h>

#include <ImageCV.h>

namespace RT
{
	void ColorBuffer2D::saveToImage(const std::string& file)const
	{
		// Create the image
		ImageCV img(width, height, this);

		// Save the image
		img.saveToFile(file);
	}
}