#pragma once

#include <SFML/Graphics.hpp>
#include "Utilties.hpp"
#include "AI.hpp"
#include <memory>

/**
* \author Jakub Baldyga
* \date 17/02/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Class responsible for showing the result of the ai.
* \details **Description:**<br>
*		Text class that shows the result of the ai on the screen.
*/

class AIOutput : public sf::Text
{
	std::unique_ptr<AI> ai;
	void updateThread(const sf::Image& image);

	const static std::string MODEL_PATH;
	const static int NUMBER_SYSTEM;

	const static int FONT_SIZE;
public:
	/// @brief Default constructor
	/// @param font - font that will be used to display the result
	AIOutput(const sf::Font& font);
	
	/// @brief Updates the result of the ai
	/// @param image - image that will be used to update the result
	void update(const sf::Image& image);
};