#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "ContentImage/ContentImage.hpp"
#include "AIOutput/AIOutput.hpp"

#include "Tools/Tool/Tool.hpp"
#include "Tools/DrawTool/DrawTool.hpp"
#include "Tools/BucketTool/BucketTool.hpp"

/**
* \author Jakub Baldyga
* \date 17/01/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Main window class.
* \details **Description:**<br>
*		Main window class, that handles all the drawing and user input. Inherits from sf::RenderWindow.
*/
class WindowManager : public sf::RenderWindow
{
    static const sf::Vector2u windowSize;
    static const int FrameRate = 60;
    std::shared_ptr<ContentImage> contentImage;
    std::unique_ptr<AIOutput> aiOutput;
    sf::Font font;

    std::unique_ptr<DrawTool> drawTool;
    std::unique_ptr<DrawTool> eraseTool;
    std::unique_ptr<BucketTool> bucketTool;
    
public:
    /// @brief Constructor for the WindowManager class.
    WindowManager();

    /// @brief Main loop of the program.
    void run();
};