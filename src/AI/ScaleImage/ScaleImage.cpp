#include "ScaleImage.hpp"
#include <algorithm>

sf::Color ScaleImage::bilinearInterpolation(const sf::Image& image, float x, float y)
{
	int x0 = int(x);
	int y0 = int(y);
	int x1 = std::min(x0 + 1, static_cast<int>(image.getSize().x) - 1);
	int y1 = std::min(y0 + 1, static_cast<int>(image.getSize().y) - 1);

	float dx = x - x0;
	float dy = y - y0;

	float value = (1 - dx) * (1 - dy) * image.getPixel(x0, y0).r +
		               dx  * (1 - dy) * image.getPixel(x1, y0).r +	
				  (1 - dx) * dy		  * image.getPixel(x0, y1).r +
				  	   dx  * dy		  * image.getPixel(x1, y1).r;

	//clamp do wartosci 0-255
	value = std::max(0.0f, std::min(255.0f, value));
	
	return sf::Color(value, value, value, 255);
}


sf::Image ScaleImage::scaleImage(const sf::Image& inputImage, int targetWidth, int targetHeight)
{
	sf::Vector2f scale;
	scale.x= static_cast<float> (targetWidth) / inputImage.getSize().x;
	scale.y = static_cast<float> (targetHeight) / inputImage.getSize().y;

	sf::Image outputImage;
	outputImage.create(targetWidth, targetHeight);

	for (int y = 0; y < targetHeight; ++y) {
		for (int x = 0; x < targetWidth; ++x) {
			float src_x = x / scale.x;
			float src_y = y / scale.y;
			outputImage.setPixel(x, y, bilinearInterpolation(inputImage, src_x, src_y));
		}
	}
	return outputImage;
}
