#include "AIOutput.hpp"

const std::string AIOutput::MODEL_PATH = GetExecutableDirectory() + "\\model.pt";
const int AIOutput::NUMBER_SYSTEM = 10;

const int AIOutput::FONT_SIZE = 30;

void AIOutput::updateThread(const sf::Image& image) {
	try {
		std::string result = "Output: " + ai->evaluate(image, NUMBER_SYSTEM).first;
		setString(result);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		setString("Output: -");
	}
}

AIOutput::AIOutput(const sf::Font& font) : sf::Text(font, "Output: -", 30) {
	ai = new AI(MODEL_PATH);
	setPosition(sf::Vector2f(100, 100));
}

void AIOutput::update(const sf::Image& image) {
	std::thread t(&AIOutput::updateThread, this, image);
	t.detach();
}

AIOutput::~AIOutput() {
	delete ai;
}