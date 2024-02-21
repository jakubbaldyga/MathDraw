#pragma once
#include <SFML/Graphics/Image.hpp>

/**
* \author Jakub Baldyga
* \date 16/12/2023ss
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Static class designed to resize an image.
* \details **Description:**<br>
*		  This class is designed to resize an image to a square or to a specified size.<br>
*		  It moves the image to the center of the new image and fills the rest with black pixels.
*/
class ResizeImage
{
public:
	/// @brief function that resizes an image to square.<br>
	///		   The new image has the same size as the larger side of the original image.
	/// @param image - image to resize
	/// @return  **sf::Image** - resized image
	static sf::Image resizeImageToSquare(const sf::Image& image);

	/// @brief function that resizes an image to a specified size.
	/// @param image - image to resize
	/// @param targetDimensions - dimensions of the new, resized image
	/// @return  **sf::Image** - resized image
	static sf::Image resizeImage(const sf::Image& inputImage, sf::Vector2u targetDimensions);

private:
	static sf::Vector2u getDimensionDifference(sf::Vector2u inputDimensions, sf::Vector2u targetDimensions);
};