#pragma once

#include <SFML/Graphics.hpp>
#include "./../Utilities/Utilties.hpp"
#include "./../AI/AI.hpp"

class AIOutput : public sf::Text
{
	AI* ai;

	void updateThread(const sf::Image& image) {
		try {
			std::string result = "Output: " + ai->evaluate(image, 10).first;
			setString(result);
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			setString("Output: -");
		}
	}

public:
	AIOutput(const sf::Font& font) : sf::Text(font, "Output: -", 30) {
		ai = new AI(GetExecutableDirectory() + "\\model.pt");
	}

	void update(const sf::Image& image) {
		std::thread t(&AIOutput::updateThread, this, image);
		t.detach();
	}

	~AIOutput() {
		delete ai;
	}
};