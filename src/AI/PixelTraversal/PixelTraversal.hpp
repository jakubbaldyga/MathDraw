#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class PixelTraversal
{

public:

	static std::vector<sf::Image> getImages(sf::Image image);

private:

	static sf::Image getSubImage(sf::Image& image, int x, int y);

	static bool validPixel(const sf::Image& image, sf::Vector3i pixel, int x, int y);

	static bool validSubImage(std::vector<sf::Vector3i> checkedPixels);

	static sf::Image creteSubImage(const std::vector<sf::Vector3i>& checkedPixels, sf::Vector2i topLeft, sf::Vector2i size);
};
