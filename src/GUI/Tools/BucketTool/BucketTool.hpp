#pragma once

#include <SFML/Graphics.hpp>
#include "../Tool/Tool.hpp"

/**
* \author Jakub Baldyga
* \date 17/012/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Class that fills the area with the same color to black.
* \details **Description:**<br>
*		Tool class that fills the area with the same color to black.
*/

class BucketTool : protected Tool
{
	bool validPixel(const sf::Image& image, sf::Vector3i pixel, int dx, int dy);
	
	public:
	
	/// @brief default Constructor
	/// @param contentImage reference to the ContentImage object
	BucketTool(std::shared_ptr<ContentImage> contentImage);

	/// @brief method that fills the area with the same color to black
	/// @param position position of the mouse
	void onMousePressed(sf::Vector2i position) override;

	/// @brief inherited method that is not used in this class.
	void onMouseReleased() override;

	/// @brief inherited method that is not used in this class
	void onMouseMoved(sf::Vector2i position) override;
};