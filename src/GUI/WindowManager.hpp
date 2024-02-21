#pragma once

#include <SFML/Graphics.hpp>
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
    const sf::Vector2u windowSize = sf::Vector2u(1200, 800);
    const int FrameRate = 60;
    ContentImage* contentImage;
    AIOutput* aiOutput;
    sf::Font font;

    DrawTool* drawTool;
    DrawTool* eraseTool;
    BucketTool* bucketTool;
    
public:
    /// @brief Constructor for the WindowManager class.
    WindowManager();

    /// @brief Main loop of the program.
    void run();

    /// @bried Destructor for the WindowManager class.
    ~WindowManager();
};