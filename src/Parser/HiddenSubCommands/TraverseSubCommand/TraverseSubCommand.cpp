#include "TraverseSubCommand.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../AI/PixelTraversal/PixelTraversal.hpp"

TraverseSubCommand::TraverseSubCommand(): SubCommand("traverse", "Traverse the image")
{
	add_argument("--image", "-i")
		.help("Specify image file")
		.nargs(1)
		.required();

	add_argument("--output", "-o")
		.help("Specify output files")
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
	std::cout << "Wygenerowano " << images.size() << " obrazow" << std::endl;
}

