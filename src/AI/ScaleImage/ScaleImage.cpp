#include "ScaleImage.hpp"
#include <algorithm>
#include "../../Utilities/Utilties.hpp"

sf::Color ScaleImage::bilinearInterpolation(const sf::Image& image, sf::Vector2f position)
{
	int x0 = int(position.x);
	int y0 = int(position.y);
	int x1 = std::min(x0 + 1, static_cast<int>(image.getSize().x) - 1);
	int y1 = std::min(y0 + 1, static_cast<int>(image.getSize().y) - 1);

	float dx = position.x - x0;
	float dy = position.y - y0;

	float value = (1 - dx) * (1 - dy) * image.getPixel(sf::Vector2u(x0, y0)).r +
		               dx  * (1 - dy) * image.getPixel(sf::Vector2u(x1, y0)).r +	
				  (1 - dx) * dy		  * image.getPixel(sf::Vector2u(x0, y1)).r +
				  	   dx  * dy		  * image.getPixel(sf::Vector2u(x1, y1)).r;

	//clamp do wartosci 0-255
	value = std::max(0.0f, std::min(255.0f, value));
	
	return sf::Color(value, value, value, 255);
}


sf::Image ScaleImage::scaleImage(const sf::Image& inputImage, sf::Vector2i targetDimenions)
{
	sf::Vector2f scale = targetDimenions / inputImage.getSize();

	sf::Image outputImage;
	outputImage.create(sf::Vector2u(targetDimenions.x, targetDimenions.y));

	for (int y = 0; y < targetDimenions.y; ++y) {
		for (int x = 0; x < targetDimenions.x; ++x) {
			sf::Vector2f src = sf::Vector2f(x, y) / scale;
			outputImage.setPixel(sf::Vector2u(x, y), bilinearInterpolation(inputImage, src));
		}
	}
	return outputImage;
}
