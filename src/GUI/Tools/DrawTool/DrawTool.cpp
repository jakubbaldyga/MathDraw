#include "DrawTool.hpp"

void DrawTool::fillPixel(sf::Vector2i cursorPosition)
{
	sf::Vector2u pos = sf::Vector2u(cursorPosition.x - contentImage->getPosition().x, cursorPosition.y - contentImage->getPosition().y);
	pos.x /= contentImage->getScale().x;
	pos.y /= contentImage->getScale().y;
	for (int x = -strokeSize / 2; x < strokeSize / 2; x++) {
		for (int y = -strokeSize / 2; y < strokeSize / 2; y++)
		{
			sf::Vector2u pos2 = sf::Vector2u(pos.x + x, pos.y + y);
			contentImage->setPixel(pos2, color);
		}
	}
}

void DrawTool::fillLine(sf::Vector2i start, sf::Vector2i end) {
	sf::Vector2i direction = end - start;
	int steps = std::max(std::abs(direction.x), std::abs(direction.y));
	for (int i = 0; i < steps; i++) {
		fillPixel(start + sf::Vector2i(direction.x * i / steps, direction.y * i / steps));
	}
	contentImage->updateTexture();
}

void DrawTool::fillPoint(sf::Vector2i cursorPosition)
{
	fillPixel(cursorPosition);
	contentImage->updateTexture();
}

DrawTool::DrawTool(std::shared_ptr<ContentImage> contentImage, sf::Color drawColor) : Tool(contentImage), color(drawColor) {
	lastPosition = sf::Vector2i(-1, -1);
}

void DrawTool::onMouseMoved(sf::Vector2i position) {
	if (!mousePressed) return;

	fillLine(lastPosition, position);
	lastPosition = position;
}

void DrawTool::onMousePressed(sf::Vector2i position) {
	mousePressed = true;

	fillPoint(position);
	lastPosition = position;
}

void DrawTool::onMouseReleased() {
	mousePressed = false;
}
