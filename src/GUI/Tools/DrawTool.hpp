#pragma once

#include <SFML/Graphics.hpp>
#include "Tool.hpp"

class DrawTool: protected Tool {

	sf::Vector2i lastPosition;
	bool mousePressed = false;
	sf::Color color;

	int strokeSize = 10;

	void fillPixel(sf::Vector2i cursorPosition)
	{
		for (int x = -strokeSize/2 ; x < strokeSize/2; x++) {
			for (int y = -strokeSize/2; y < strokeSize/2; y++)
			{
				sf::Vector2u pos = sf::Vector2u(cursorPosition.x - contentImage->getPosition().x + x, cursorPosition.y - contentImage->getPosition().y + y);
				contentImage->setPixel(pos, color);
			}
		}
	}

	void fillLine(sf::Vector2i start, sf::Vector2i end) {
		sf::Vector2i direction = end - start;
		int steps = std::max(std::abs(direction.x), std::abs(direction.y));
		for (int i = 0; i < steps; i++) {
			fillPixel(start + sf::Vector2i(direction.x * i / steps, direction.y * i / steps));
		}
		contentImage->updateTexture();
	}

	void fillPoint(sf::Vector2i cursorPosition)
	{
		fillPixel(cursorPosition);
		contentImage->updateTexture();
	}

public:

	DrawTool(ContentImage& contentImage, sf::Color color) : Tool(contentImage) {
		lastPosition = sf::Vector2i(-1, -1);
		this->color = color;
	}

	void onMouseMoved(sf::Vector2i position) override {
		if(!mousePressed) return;

		fillLine(lastPosition, position);
		lastPosition = position;
	}

	void onMousePressed(sf::Vector2i position) override {
		mousePressed = true;

		fillPoint(position);
		lastPosition = position;
	}

	void onMouseReleased() override {
		mousePressed = false;
	}
};