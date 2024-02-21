#include "ContentImage.hpp"
#include "../../Utilities/Utilties.hpp"

void ContentImage::clampImagePosition()
{
    sf::Vector2f position = getPosition();

    position.x = std::max(float(-5000 * getScale().x + (int)windowSize.x), std::min(0.f, position.x));
    position.y = std::max(float(-5000 * getScale().y + (int)windowSize.y), std::min(0.f, position.y));

    std::cout << position.x << " " << position.y << std::endl;
    setPosition(position);
}


void ContentImage::copyImage(sf::Image& destination, sf::Image& source) {
    destination.create(source.getSize(), source.getPixelsPtr());
}

void ContentImage::zoom(float factor) {
    sf::Vector2f centerBeforeZoom = (windowSize/2 - getPosition()) / getScale();
    scale(sf::Vector2f(factor, factor));
    sf::Vector2f newPosition = windowSize/2 - centerBeforeZoom * getScale();
    setPosition(newPosition);
    clampImagePosition();
}



ContentImage::ContentImage(sf::Vector2u windowSize) : sf::Sprite(texture), windowSize(windowSize)
{
    image = sf::Image();
    image.create(imageSize, sf::Color::Black);

    updateTexture();
    setTexture(texture, true);
    setPosition(imageStartingPosition);

    copyImage(previousImage, image);
    copyImage(tempImage, image);

    std::cout<< getPosition().x << " " << getPosition().y << std::endl;
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
        clampImagePosition();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        move(sf::Vector2f(0, -movementSpeed));
        clampImagePosition();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        move(sf::Vector2f(movementSpeed, 0));
        clampImagePosition();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        move(sf::Vector2f(-movementSpeed, 0));
        clampImagePosition();
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
    if(getScale().x > 2.5f) return;
    zoom(1.1f);
}

void ContentImage::zoomOut() {
    if(getScale().x < 0.5f) return;
    zoom(0.9f);
}

void ContentImage::clear() {
    image = sf::Image();
    image.create(imageSize, sf::Color::Black);
    copyImage(previousImage, image);
    copyImage(tempImage, image);
    updateTexture();
    savePreviousImage();
}
