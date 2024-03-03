#pragma once

#include <SFML/Graphics.hpp>
#include "../Tool/Tool.hpp"

/**
* \author Jakub Baldyga
* \date 17/02/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Class that draws on the image with the selected color.
* \details **Description:**<br>
*		Tool class that draws on the image with the selected color.
*/

class DrawTool: protected Tool {

	sf::Vector2i lastPosition;
	bool mousePressed = false;
	
	const sf::Color color;
	const int strokeSize = 10;

	void fillPixel(sf::Vector2i cursorPosition);
	void fillLine(sf::Vector2i start, sf::Vector2i end);
	void fillPoint(sf::Vector2i cursorPosition);
public:

	/// @brief Constructor
	/// @param contentImage Reference to the image to be drawn on
	/// @param drawColor - Color of the drawing
	DrawTool(std::shared_ptr<ContentImage> contentImage, sf::Color drawColor);

	/// @brief inherited from Tool. Draws a line between the last and the current position of the mouse
	/// @param position position of the mouse
	void onMouseMoved(sf::Vector2i position) override;

	/// @brief inherited from Tool. Begins drawing, draws a point at the position of the mouse
	/// @param position position of the mouse
	void onMousePressed(sf::Vector2i position) override;

	/// @brief inherited from Tool. Stops drawing
	void onMouseReleased() override;
};