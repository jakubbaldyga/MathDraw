#pragma once

#include <SFML/Graphics.hpp>
#include "../../ContentImage/ContentImage.hpp"

class Tool {

protected:
	ContentImage* contentImage;

public:

	///@brief Constructor
	Tool(ContentImage& contentImage) {
		this->contentImage = &contentImage;
	}

	/// function to be called when the tool is selected and mouse has clicked
	virtual void onMouseMoved(sf::Vector2i position) = 0;

	/// function to be called when the tool is selected and the mouse is moved
	virtual void onMousePressed(sf::Vector2i position) = 0;

	/// function to be called when the tool is selected and the mouse is released
	virtual void onMouseReleased() = 0;
};