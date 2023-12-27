#include "AI/AI.hpp"
#include <iostream>
#include <argparse/argparse.hpp>
#include "AI/ScaleImage/ScaleImage.hpp"
#include "AI/PixelTraversal/PixelTraversal.hpp"

int main(int argc, char* argv[])
{
	const std::string wersjaProgramu = "1.0.0";

	argparse::ArgumentParser program("MathDraw");

	argparse::ArgumentParser recogniseCommand("recognise");
	recogniseCommand.add_description("Recognise number from image");

	recogniseCommand.add_argument("--image", "-i")
		.help("Specify image file")
		.nargs(1)
		.required();

	recogniseCommand.add_argument("--model", "-m")
		.help("Specify model file")
		.nargs(1)
		.default_value(std::string("model.pt"));

	recogniseCommand.add_argument("--number_system","-n")
		.help ("Specify number system")
		.nargs(1)
		.default_value(int(10))
		.choices(2,8,10)
		.scan<'i', int>();

	program.add_subparser(recogniseCommand);

	argparse::ArgumentParser scaleCommand("scale");
	scaleCommand.add_description("Scale image");
	scaleCommand.set_suppress(true);

	scaleCommand.add_argument("--image", "-i")
		.help("Specify image file")
		.nargs(1)
		.required();

	scaleCommand.add_argument("--width", "-w")
		.help("Specify width")
		.nargs(1)
		.scan<'i', int>()
		.required();

	scaleCommand.add_argument("--height", "-h")
		.help("Specify height")
		.nargs(1)
		.scan<'i', int>()
		.required();

	scaleCommand.add_argument("--output", "-o")
		.help("Specify output file")
		.nargs(1)
		.default_value("scaledImage.png");

	program.add_subparser(scaleCommand);
	
	argparse::ArgumentParser traverseCommand("traverse");
	traverseCommand.add_description("Traverse image");
	traverseCommand.set_suppress(true);

	traverseCommand.add_argument("--image", "-i")
		.help("Specify image file")
		.nargs(1)
		.required();

	traverseCommand.add_argument("--output", "-o")
		.help("Specify output files")
		.nargs(1)
		.default_value("traversedImage.png");

	program.add_subparser(traverseCommand);

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		return -1;
	}
	
	if (program.is_subcommand_used(recogniseCommand))
	{
		std::string fileName = recogniseCommand.get<std::string>("-i");
		std::string modelFile = recogniseCommand.get<std::string>("-m");
		int numberSystem = recogniseCommand.get<int>("-n");
	
		sf::Image sourceImage;
		if (!sourceImage.loadFromFile(fileName))
			return -1;
		try {
			AI ai(modelFile);
			std::cout << "Wynik: " << ai.evaluate(sourceImage, false) << std::endl;
		}
		catch (const std::exception& err) {
			std::cerr << err.what() << std::endl;
			return -1;
		}
		return 0;
	}

	if (program.is_subcommand_used(scaleCommand))
	{
		std::string fileName = scaleCommand.get<std::string>("-i");
		int width = scaleCommand.get<int>("-w");
		int height = scaleCommand.get<int>("-h");
		std::string output = scaleCommand.get<std::string>("-o");

		sf::Image sourceImage;
		if (!sourceImage.loadFromFile(fileName))
			return -1;

		sf::Image scaledImage = ScaleImage::scaleImage(sourceImage, width, height);
		scaledImage.saveToFile(output);
		std::cout << "Zeskalowano!" << std::endl;
		return 0;
	}

	if (program.is_subcommand_used(traverseCommand)) {
		std::string fileName = traverseCommand.get<std::string>("-i");
		std::string output = traverseCommand.get<std::string>("-o");
		
		std::string outputFileName = output.substr(0, output.find_last_of('.'));
		std::string outputFileExtension = output.substr(output.find_last_of('.'));

		sf::Image sourceImage;
		if (!sourceImage.loadFromFile(fileName))
			return -1;

		std::vector<sf::Image> images = PixelTraversal::getImages(sourceImage);

		for (int i = 0; i < images.size(); i++)
		{
			images[i].saveToFile(outputFileName + std::to_string(i) + outputFileExtension);
		}
		std::cout<<"Wygenerowano " << images.size() << " obrazow" << std::endl;
		return 0;
	}
}