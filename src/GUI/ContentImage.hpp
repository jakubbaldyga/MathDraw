#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

bool operator==(sf::Image i, sf::Image j) {
    if (i.getSize() != j.getSize()) return false;
    for (int x = 0; x < i.getSize().x; x++) {
        for (int y = 0; y < i.getSize().y; y++) {
            if (i.getPixel(sf::Vector2u(x, y)) != j.getPixel(sf::Vector2u(x, y))) return false;
        }
    }
    return true;
}

class ContentImage : public sf::Sprite
{
    sf::Image image;
    sf::Texture texture;

    const sf::Vector2u imageSize = sf::Vector2u(5000, 5000);
    const sf::Vector2f imageStartingPosition = sf::Vector2f(-2500 + 600, -2500 + 400);

    const int movementSpeed = 5;

    sf::Image previousImage;
    sf::Image tempImage;

public:

    ContentImage(): sf::Sprite(texture)
    {
        image = sf::Image();
        image.create(imageSize, sf::Color::Black);
        
        updateTexture();
        setTexture(texture, true);
        setPosition(imageStartingPosition);

        previousImage.copy(image, sf::Vector2u(0,0));
        tempImage.copy(image, sf::Vector2u(0,0));
    }

    void setPixel(sf::Vector2u position, sf::Color color) {
        image.setPixel(position, color);
    }

    void updateTexture() {
        texture.loadFromImage(image);
    }

    sf::Image getImage() {
		return image;
	}

    void handleMovement() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            move(sf::Vector2f(0, movementSpeed));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            move(sf::Vector2f(0, -movementSpeed));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            move(sf::Vector2f(movementSpeed, 0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            move(sf::Vector2f(-movementSpeed, 0));
        }
    }
};