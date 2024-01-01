#pragma once
#include <SFML/Graphics/Image.hpp>

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Static class designed to scale image.
* \details **Description:**<br>
*		  Scales given image <br>
*/
class ScaleImage
{
public:
	/// @brief function that scales the image
	/// @param inputImage - image to scale
	/// @param targetDimension - target dimensions of the sclaed image
	/// @return  **sf::Image** - scaled image
	static sf::Image scaleImage(const sf::Image& inputImage, sf::Vector2i targetDimension);

private:
	static sf::Color bilinearInterpolation(const sf::Image& image, sf::Vector2f position);
};
