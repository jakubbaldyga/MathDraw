#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Static class designed to traverse things on given image.
* \details **Description:**<br>
*		  Every white part of the image which is separated and surrounded by black pixels <br>
*		  will be extracted and returned in their own images individually<br>
*/
class PixelTraversal
{

public:
	/// @brief function that traverses the image and returns the subimages
	/// @param image - image to traverse
	/// @return  **vector<sf::Image>** - vector of subimages

	static std::vector<sf::Image> getImages(sf::Image image);

private:

	static sf::Image getSubImage(sf::Image& image, int x, int y);

	static bool validPixel(const sf::Image& image, sf::Vector3i pixel, int dx, int dy);

	static bool validSubImage(std::vector<sf::Vector3i> checkedPixels);

	static sf::Image creteSubImage(const std::vector<sf::Vector3i>& checkedPixels, sf::Vector2i topLeft, sf::Vector2i size);
};
