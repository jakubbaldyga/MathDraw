#include <SFML/Graphics.hpp>
#include "ContentImage.hpp"

class WindowManager : public sf::RenderWindow
{
    ContentImage contentImage;

public:
    WindowManager() : sf::RenderWindow(sf::VideoMode(sf::Vector2u(1200, 800)), "SFML works!")
    {
        this->setFramerateLimit(60);
        contentImage = ContentImage();
    }

    void run()
    {
        while (this->isOpen())
        {
            sf::Event event;
            while (this->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    this->close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        contentImage.fillPixel(sf::Mouse::getPosition(*this), sf::Color::Black);
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                    {
                        contentImage.fillPixel(sf::Mouse::getPosition(*this), sf::Color::White);
                    }
                }
            }

            
            this->draw(contentImage);
            this->display();
        }
    }
};