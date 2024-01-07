#include "ResizeSubCommand.hpp"
#include <SFML/Graphics.hpp>
#include "../../../AI/ResizeImage/ResizeImage.hpp"
#include <iostream>

ResizeSubCommand::ResizeSubCommand(): SubCommand("resize", "Resize the image")
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
	std::cout << "Zmieniono rozmiar i wygenerowano " + output << std::endl;
	return;
}