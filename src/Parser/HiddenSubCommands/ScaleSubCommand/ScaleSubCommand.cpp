#include "ScaleSubCommand.h"
#include <argparse/argparse.hpp>
#include <SFML/Graphics.hpp>
#include "../../../AI/ScaleImage/ScaleImage.hpp"

ScaleSubCommand::ScaleSubCommand() : SubCommand("scale", "Scale the image")
{	
	add_argument("--image", "-i")
		.help("Specify image file")
		.nargs(1)
		.required();

	add_argument("--width", "-w")
		.help("Specify width")
		.nargs(1)
		.scan<'i', int>()
		.required();

	add_argument("--height", "-he")
		.help("Specify height")
		.nargs(1)
		.scan<'i', int>()
		.required();

	add_argument("--output", "-o")
		.help("Specify output file")
		.nargs(1)
		.default_value("scaledImage.png");
}

void ScaleSubCommand::doCommand()
{
	std::string fileName = get<std::string>("-i");
	std::string output = get<std::string>("-o");

	int width = get<int>("-w");
	int height = get<int>("-h");


	sf::Image sourceImage;
	
	if (!sourceImage.loadFromFile(fileName))
		return;

	sf::Image scaledImage = ScaleImage::scaleImage(sourceImage, sf::Vector2i(width, height) );
	scaledImage.saveToFile(output);
	std::cout << "Zeskalowano i wygenerowano " + output << std::endl;
	return;
}
