#include <SFML/Graphics.hpp>
#include <iostream>

class ContentImage : public sf::Drawable
{
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite = sf::Sprite(texture);

    //sf::Vector2f imagePosition = sf::Vector2f(2500 - 600, 2500 - 400);
    sf::Vector2f imagePosition = sf::Vector2f(0,0);

public:
    ContentImage()
    {
        image.create(sf::Vector2u(5000, 5000), sf::Color::Blue);

        for (int i = 0; i < 5000; i++)
        {
            for (int j = 0; j < 5000; j++)
            {
				image.setPixel(sf::Vector2u(i, j), sf::Color::Blue);
			}
		}

        if (!texture.loadFromImage(image)) {
			std::cout<<"Error loading texture from image"<<std::endl;
		}
        sprite = sf::Sprite(texture);
        sprite.setTexture(texture);
        sprite.setPosition(imagePosition);
    }

    void fillPixel(sf::Vector2i cursorPosition, sf::Color color)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                sf::Vector2u pos = sf::Vector2u(cursorPosition.x + i, cursorPosition.y + j);
                image.setPixel(pos, color);
            }
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }

    sf::Color getPixelColor(sf::Vector2i cursorPosition) 
    {
        sf::Vector2u pos = sf::Vector2u(cursorPosition.x, cursorPosition.y);
		return image.getPixel(pos);
	}

    void moveImage(sf::Vector2f direction)
    {
        imagePosition += direction;
        sprite.setPosition(imagePosition);
    }

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override
    {
        target.draw(this->sprite, states);
    }
};