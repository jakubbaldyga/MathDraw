#pragma once

#include <SFML/Graphics.hpp>
#include "../ContentImage.hpp"

class Tool {

protected:
	ContentImage* contentImage;

public:
	Tool(ContentImage& contentImage) {
		this->contentImage = &contentImage;
	}

	virtual void onMouseMoved(sf::Vector2i position) = 0;
	virtual void onMousePressed(sf::Vector2i position) = 0;
	virtual void onMouseReleased() = 0;
};