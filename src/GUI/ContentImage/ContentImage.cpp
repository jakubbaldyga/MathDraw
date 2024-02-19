#include "ContentImage.hpp"

void ContentImage::copyImage(sf::Image& destination, sf::Image& source) {
    destination.create(source.getSize(), source.getPixelsPtr());
}

ContentImage::ContentImage() : sf::Sprite(texture)
{
    image = sf::Image();
    image.create(imageSize, sf::Color::Black);

    updateTexture();
    setTexture(texture, true);
    setPosition(imageStartingPosition);

    copyImage(previousImage, image);
    copyImage(tempImage, image);
}

void ContentImage::setPixel(sf::Vector2u position, sf::Color color) {
    image.setPixel(position, color);
}

void ContentImage::savePreviousImage() {
    copyImage(previousImage, tempImage);
    copyImage(tempImage, image);

    hasUndone = false;
}

void ContentImage::handleMovement() {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
        zoomIn();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {
        zoomOut();
    }
}

void ContentImage::updateTexture() {
    texture.loadFromImage(image);
}

sf::Image ContentImage::getImage() {
    return image;
}

void ContentImage::zoomIn() {
    scale(sf::Vector2f(1.1f, 1.1f));
    setPosition(getPosition() * 1.1f);
}

void ContentImage::zoomOut() {
    scale(sf::Vector2f(0.9f, 0.9f));
    setPosition(getPosition() * 0.9f);
}

void ContentImage::clear() {
    image = sf::Image();
    image.create(imageSize, sf::Color::Black);
    copyImage(previousImage, image);
    copyImage(tempImage, image);
    updateTexture();
    savePreviousImage();
}
