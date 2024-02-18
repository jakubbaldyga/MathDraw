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

void copyImage(sf::Image& destination, sf::Image& source) {
    destination.create(source.getSize(), source.getPixelsPtr());
}

class ContentImage : public sf::Sprite
{
    sf::Image image;
    sf::Texture texture;

    const sf::Vector2u imageSize = sf::Vector2u(5000, 5000);
    const sf::Vector2f imageStartingPosition = sf::Vector2f(-2500 + 600, -2500 + 400);

    const int movementSpeed = 5;

    bool hasUndone = false;
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

        copyImage(previousImage, image);
        copyImage(tempImage, image);
    }

    void setPixel(sf::Vector2u position, sf::Color color) {
        image.setPixel(position, color);
    }

    void savePreviousImage() {
        copyImage(previousImage, tempImage);
        copyImage(tempImage, image);

        hasUndone = false;
    }

    void loadPreviousImage() {
        if (hasUndone) return;
        copyImage(image, previousImage);
        copyImage(tempImage, previousImage);
        updateTexture();

        hasUndone = true;
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
			zoomIn();
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {
			zoomOut();
		}
    }

    void updateTexture() {
        texture.loadFromImage(image);
    }

    sf::Image getImage() {
		return image;
	}

    void zoomIn() {
		scale(sf::Vector2f(1.1f, 1.1f));
        setPosition(getPosition() * 1.1f);
	}

    void zoomOut() {
        scale(sf::Vector2f(0.9f, 0.9f));
        setPosition(getPosition() * 0.9f);
    }

    void clear() {
        image = sf::Image();
        image.create(imageSize, sf::Color::Black);
        copyImage(previousImage, image);
        copyImage(tempImage, image);
        updateTexture();
        savePreviousImage();
    }
};