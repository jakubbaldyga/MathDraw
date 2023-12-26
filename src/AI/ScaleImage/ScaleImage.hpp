#pragma once
#include <SFML/Graphics/Image.hpp>

class ScaleImage
{

public:
	static sf::Image scaleImage(const sf::Image& inputImage, int targetWidth, int targetHeight);

private:
	static sf::Color bilinearInterpolation(const sf::Image& image, float x, float y);
};
