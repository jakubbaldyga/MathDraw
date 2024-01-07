#include "TraverseSubCommand.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../AI/PixelTraversal/PixelTraversal.hpp"
#include "../../../Utilities/Strings.hpp"

TraverseSubCommand::TraverseSubCommand(): SubCommand(Strings::TRAVERSE_COMMAND_NAME, Strings::TRAVERSE_COMMAND_DESCRIPTION)
{
	add_argument("--image", "-i")
		.help(Strings::SPECIFY_IMAGE_FILE)
		.nargs(1)
		.required();

	add_argument("--output", "-o")
		.help(Strings::SPECIFY_OUTPUT_FILE)
		.nargs(1)
		.default_value("traversedImage.png");
}

void TraverseSubCommand::doCommand()
{
	std::string fileName = get<std::string>("-i");
	std::string output = get<std::string>("-o");

	std::string outputFileName = output.substr(0, output.find_last_of('.'));
	std::string outputFileExtension = output.substr(output.find_last_of('.'));

	sf::Image sourceImage;
	if (!sourceImage.loadFromFile(fileName))
		return;

	std::vector<sf::Image> images = PixelTraversal::getImages(sourceImage);

	for (int i = 0; i < images.size(); i++)
	{
		images[i].saveToFile(outputFileName + std::to_string(i) + outputFileExtension);
	}
	std::cout << "Generated " << images.size() << " images" << std::endl;
}

