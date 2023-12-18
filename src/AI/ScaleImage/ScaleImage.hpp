#pragma once
#include <SFML/Graphics/Image.hpp>

class ScaleImage
{
	static sf::Color bilinearInterpolation(const sf::Image& image, float x, float y);

public:
	static sf::Image scaleImage(const sf::Image& inputImage, int targetWidth=28, int targetHeight=28);
};
