#pragma once

#include <SFML/Graphics.hpp>
#include "../../ContentImage/ContentImage.hpp"
#include <memory> 

class Tool {

protected:
    std::shared_ptr<ContentImage> contentImage; // Change to std::unique_ptr

public:

    ///@brief Constructor
    Tool(std::shared_ptr<ContentImage> contentImage) : contentImage(contentImage) {} // Modify constructor to accept unique_ptr

    /// function to be called when the tool is selected and mouse has clicked
    virtual void onMouseMoved(sf::Vector2i position) = 0;

    /// function to be called when the tool is selected and the mouse is moved
    virtual void onMousePressed(sf::Vector2i position) = 0;

    /// function to be called when the tool is selected and the mouse is released
    virtual void onMouseReleased() = 0;
};