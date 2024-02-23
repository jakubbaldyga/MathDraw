#include "ScaleSubCommand.hpp"
#include <argparse/argparse.hpp>
#include <SFML/Graphics.hpp>
#include "../../../AI/ScaleImage/ScaleImage.hpp"
#include "Strings.hpp"

ScaleSubCommand::ScaleSubCommand() : SubCommand(Strings::SCALE_COMMAND_NAME, Strings::SCALE_COMMAND_DESCRIPTION)
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
		.default_value("scaledImage.png");
}

void ScaleSubCommand::doCommand()
{
	std::string fileName = get<std::string>("-i");
	std::string output = get<std::string>("-o");

	int width = get<int>("-w");
	int height = get<int>("-he");


	sf::Image sourceImage;
	
	if (!sourceImage.loadFromFile(fileName))
		return;

	sf::Image scaledImage = ScaleImage::scaleImage(sourceImage, sf::Vector2i(width, height) );
	scaledImage.saveToFile(output);
	std::cout << "Scaled and generated " + output << std::endl;
	return;
}
