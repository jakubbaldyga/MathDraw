#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/**
* \author Jakub Baldyga
* \date 17/02/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Class responsible for showing the image on the screen.
* \details **Description:**<br>
*		This class is responsible for showing the image on the screen. It also allows for moving the image, zooming in and out, and undoing the last action.
*/

class ContentImage : public sf::Sprite
{
    sf::Image image;
    sf::Texture texture;

    static const sf::Vector2u imageSize;
    static const sf::Vector2f imageStartingPosition;
    const sf::Vector2u windowSize;

    static const int movementSpeed;

    bool hasUndone = false;
    sf::Image previousImage;
    sf::Image tempImage;

    void clampImagePosition();

    void copyImage(sf::Image& destination, sf::Image& source);

    void zoom(float factor);

public:

    /// @brief Constructor of the class.
    ContentImage(sf::Vector2u windowSize);

    /// @brief Sets the pixel at the given position to the given color.
    /// @param position The position of the pixel.
    /// @param color The color of the pixel.
    void setPixel(sf::Vector2u position, sf::Color color);

    /// @brief Saves the image so that it can be undone later.
    void savePreviousImage();

    /// @brief Function that allows undoing the last action.
    void loadPreviousImage() {
        if (hasUndone) return;
        copyImage(image, previousImage);
        copyImage(tempImage, previousImage);
        updateTexture();

        hasUndone = true;
    }

    /// @brief Function that catches the event and handles the movement of the image.
    void handleMovement();

    /// @brief Function that updates the texture of the image, after the image(sf::Image) has been changed.
    void updateTexture();

    /// @brief Function that returns the current image.
    /// @return The current image.
    sf::Image getImage() const;

    /// @brief Zooms in the image.
    void zoomIn();

    /// @brief Zooms out the image.
    void zoomOut();

    /// @brief Clears the image.
    void clear();
};