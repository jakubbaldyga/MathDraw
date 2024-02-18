#pragma once

#include <SFML/Graphics.hpp>
#include "ContentImage.hpp"
#include "AIOutput.hpp"

#include "Tools/Tool.hpp"
#include "Tools/DrawTool.hpp"

class WindowManager : public sf::RenderWindow
{
    ContentImage contentImage;
    AIOutput* aiOutput;
    sf::Font font;

    DrawTool* drawTool;
    DrawTool* eraseTool;
    
public:
    WindowManager() : sf::RenderWindow(sf::VideoMode(sf::Vector2u(1200, 800)), "SFML works!")
    {
        this->setFramerateLimit(60);

        font = sf::Font();
        font.loadFromFile("font.ttf");

        aiOutput = new AIOutput(font);
        aiOutput->setPosition(sf::Vector2f(100, 100));

        drawTool = new DrawTool(contentImage, sf::Color::White);
        eraseTool = new DrawTool(contentImage, sf::Color::Black);
    }
    void run()
    {
        while (this->isOpen())
        {
            sf::Event event;
            if (this->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    this->close();

                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*this);
                    drawTool->onMouseMoved(mousePosition);
                    eraseTool->onMouseMoved(mousePosition);
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*this);
                    std::cout<< "Mouse pressed at " << mousePosition.x << " " << mousePosition.y << std::endl;
                    if (event.mouseButton.button == sf::Mouse::Button::Right)
                        eraseTool->onMousePressed(mousePosition);
                    
                    else if (event.mouseButton.button == sf::Mouse::Button::Left)
                        drawTool->onMousePressed(mousePosition);
                }

                if(event.type == sf::Event::MouseButtonReleased) {

                    if (event.mouseButton.button == sf::Mouse::Button::Right)
                        eraseTool->onMouseReleased();

                    else if(event.mouseButton.button == sf::Mouse::Button::Left)
                        drawTool->onMouseReleased();
                    
                    aiOutput->update(contentImage.getImage());
                    contentImage.savePreviousImage();
                }

                //undo
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Z && event.key.control) {
					contentImage.loadPreviousImage();
                    aiOutput->update(contentImage.getImage());
				}

                //erase everything
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::E && event.key.control) {
					contentImage.clear();
					aiOutput->update(contentImage.getImage());
				}
            }

            contentImage.handleMovement();

            this->clear(sf::Color::White);
            this->draw(contentImage);
            this->draw(*aiOutput);
            this->display();
        }
    }

    ~WindowManager() {
        delete aiOutput;
        delete drawTool;
	}
};