#include "RecogniseSubCommand.hpp"
#include "../../AI/AI.hpp"
#include <SFML/Graphics.hpp>
#include "../../Utilities/Utilties.hpp"
#include "../../Utilities/Strings.hpp"
RecogniseSubCommand::RecogniseSubCommand() : SubCommand(Strings::RECOGNISE_COMMAND_NAME, Strings::RECOGNISE_COMMAND_DESCRRIPTION)
{
	add_argument("--image", "-i")
		.help(Strings::SPECIFY_IMAGE_FILE)
		.nargs(1)
		.required();

	add_argument("--model", "-m")
		.help(Strings::SPECIFY_MODEL_FILE)
		.nargs(1)
		.default_value(std::string(GetExecutableDirectory() + "\\model.pt"));

	add_argument("--number_system", "-n")
		.help(Strings::SPECIFY_NUMBER_BASE_SYSTEM)
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
		std::cout << "Outcome: " << result.first << std::endl;
		std::cout << "Outcome in decimal system: " << result.second << std::endl;
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return;
	}
}
