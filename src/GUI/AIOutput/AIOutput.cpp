#include "AIOutput.hpp"

void AIOutput::updateThread(const sf::Image& image) {
	try {
		std::string result = "Output: " + ai->evaluate(image, 10).first;
		setString(result);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		setString("Output: -");
	}
}

AIOutput::AIOutput(const sf::Font& font) : sf::Text(font, "Output: -", 30) {
	ai = new AI(GetExecutableDirectory() + "\\model.pt");
}

void AIOutput::update(const sf::Image& image) {
	std::thread t(&AIOutput::updateThread, this, image);
	t.detach();
}

AIOutput::~AIOutput() {
	delete ai;
}