#include "ResizeSubCommand.hpp"
#include <SFML/Graphics.hpp>
#include "../../../AI/ResizeImage/ResizeImage.hpp"
#include <iostream>
#include "../../../Utilities/Strings.hpp"

ResizeSubCommand::ResizeSubCommand(): SubCommand(Strings::RESIZE_COMMAND_NAME, Strings::RESIZE_COMMAND_DESCRRIPTION )
{
	add_argument("--image", "-i")
		.help(Strings::SPECIFY_IMAGE_FILE)
		.nargs(1)
		.required();

	add_argument("--width", "-w")
		.help(Strings::SPECIFY_WIDTH)
		.nargs(1)
		.scan<'i', int>()
		.required();

	add_argument("--height", "-he")
		.help(Strings::SPECIFY_HEIGHT)
		.nargs(1)
		.scan<'i', int>()
		.required();

	add_argument("--output", "-o")
		.help(Strings::SPECIFY_OUTPUT_FILE)
		.nargs(1)
		.default_value("resizedImage.png");
}

void ResizeSubCommand::doCommand()
{
	std::string fileName = get<std::string>("-i");
	std::string output = get<std::string>("-o");

	int width = get<int>("-w");
	int height = get<int>("-he");


	sf::Image sourceImage;

	if (!sourceImage.loadFromFile(fileName))
		return;

	sf::Image resizedImage = ResizeImage::resizeImage(sourceImage, sf::Vector2u(width, height));
	resizedImage.saveToFile(output);
	std::cout << "Resized and generated " + output << std::endl;
	return;
}