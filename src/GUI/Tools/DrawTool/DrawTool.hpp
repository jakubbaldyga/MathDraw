#pragma once

#include <SFML/Graphics.hpp>
#include "../Tool/Tool.hpp"

/**
* \author Jakub Baldyga
* \date 17/01/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Class that draws on the image with the selected color.
* \details **Description:**<br>
*		Tool class that draws on the image with the selected color.
*/

class DrawTool: protected Tool {

	sf::Vector2i lastPosition;
	bool mousePressed = false;
	sf::Color color;

	int strokeSize = 10;

	void fillPixel(sf::Vector2i cursorPosition);

	void fillLine(sf::Vector2i start, sf::Vector2i end);

	void fillPoint(sf::Vector2i cursorPosition);

public:

	/// @brief Constructor
	/// @param contentImage Reference to the image to be drawn on
	/// @param color Color of the drawing
	DrawTool(ContentImage& contentImage, sf::Color color);

	/// @brief inherited from Tool
	void onMouseMoved(sf::Vector2i position) override;

	/// @brief inherited from Tool
	void onMousePressed(sf::Vector2i position) override;

	/// @brief inherited from Tool
	void onMouseReleased() override;
};