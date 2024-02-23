#include "WindowManager.hpp"

WindowManager::WindowManager() : sf::RenderWindow(sf::VideoMode(sf::Vector2u(1200, 800)), "MathDraw")
{
    this->setFramerateLimit(FrameRate);

    if(!font.loadFromFile("font.ttf")) std::cout << "Font not loaded" << std::endl;

    aiOutput = new AIOutput(font);

    contentImage = new ContentImage(windowSize);

    drawTool = new DrawTool(contentImage, sf::Color::White);
    eraseTool = new DrawTool(contentImage, sf::Color::Black);
    bucketTool = new BucketTool(contentImage);
}

void WindowManager::run()
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

                if (event.mouseButton.button == sf::Mouse::Button::Right)
                    eraseTool->onMousePressed(mousePosition);

                else if (event.mouseButton.button == sf::Mouse::Button::Left)
                    drawTool->onMousePressed(mousePosition);

                else if (event.mouseButton.button == sf::Mouse::Button::Middle)
                    bucketTool->onMousePressed(mousePosition);
            }

            if (event.type == sf::Event::MouseButtonReleased) {

                if (event.mouseButton.button == sf::Mouse::Button::Right)
                    eraseTool->onMouseReleased();

                else if (event.mouseButton.button == sf::Mouse::Button::Left)
                    drawTool->onMouseReleased();

                aiOutput->update(contentImage->getImage());
                contentImage->savePreviousImage();
            }

            //undo
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Z && event.key.control) {
                contentImage->loadPreviousImage();
                aiOutput->update(contentImage->getImage());
            }

            //erase everything
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::E && event.key.control) {
                contentImage->clear();
                aiOutput->update(contentImage->getImage());
            }
        }

        contentImage->handleMovement();

        this->clear(sf::Color::White);
        this->draw(*contentImage);
        this->draw(*aiOutput);
        this->display();
    }
}

WindowManager::~WindowManager() {
    delete aiOutput;
    delete drawTool;
    delete eraseTool;
    delete bucketTool;
    delete contentImage;
}
