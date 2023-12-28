#include "RecogniseSubCommand.h"
#include "AI/AI.hpp"
#include <SFML/Graphics.hpp>

RecogniseSubCommand::RecogniseSubCommand() : SubCommand("recognise", "Recognise number from image")
{
	add_argument("--image", "-i")
		.help("Specify image file")
		.nargs(1)
		.required();

	add_argument("--model", "-m")
		.help("Specify model file")
		.nargs(1)
		.default_value(std::string("model.pt"));

	add_argument("--number_system", "-n")
		.help("Specify number system")
		.nargs(1)
		.default_value(int(10))
		.choices(2, 8, 10)
		.scan<'i', int>();
}

void RecogniseSubCommand::doCommand()
{
	std::string fileName = get<std::string>("-i");
	std::string modelFile = get<std::string>("-m");
	int numberSystem = get<int>("-n");

	sf::Image sourceImage;
	if (!sourceImage.loadFromFile(fileName))
		return;
	
	try {
		AI ai(modelFile);
		std::pair<std::string, int> result = ai.evaluate(sourceImage, numberSystem);
		std::cout << "Wynik: " << result.first << std::endl;
		std::cout << "Wynik w systemie dziesietnym: " << result.second << std::endl;
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return;
	}
}
