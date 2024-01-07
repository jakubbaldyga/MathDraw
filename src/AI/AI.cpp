#include <torch/torch.h>
#include <SFML/Graphics.hpp>
#include "PixelTraversal/PixelTraversal.hpp"
#include "ScaleImage/ScaleImage.hpp"
#include "AI.hpp"
#include "ResizeImage/ResizeImage.hpp"

const int AI::TRAINED_IMAGE_WIDTH = 28;
const int AI::TRAINED_IMAGE_HEIGHT = 28;
const double AI:: DEVIATION_BIAS = 0.1307;
const double AI::DEVIATION_SCALE = 1/0.3081;

torch::Tensor AI::preprocessImage(const sf::Image& image)
{
	torch::Tensor imageTensor = torch::zeros({ 1, TRAINED_IMAGE_WIDTH, TRAINED_IMAGE_HEIGHT }, torch::kFloat32);
	for (int i = 0; i < TRAINED_IMAGE_WIDTH; ++i) {
		for (int j = 0; j < TRAINED_IMAGE_HEIGHT; ++j) {
			//r=g=b
			imageTensor[0][i][j] = static_cast<float>(image.getPixel(j,i).r) / 255.f;
		}
	}

	// Tak zostal wyuczony ten model - przy tych parametrach
	imageTensor = (imageTensor - DEVIATION_BIAS) * DEVIATION_SCALE;
	imageTensor = imageTensor.unsqueeze(0);

	return imageTensor;
}

int AI::evaluateImage(const sf::Image& image)
{
	torch::Tensor inputTensor = preprocessImage(image);
	inputTensor = inputTensor.to(device);
	torch::Tensor output = model.forward(inputTensor);
	auto pred = output.argmax(1);
	return pred.item<int>();
}

AI::AI(const std::string& path)
{
	torch::manual_seed(0);
	device = torch::Device(torch::kCPU);
	loadModel(path);
	model.eval();
}

std::pair<std::string, int> AI::evaluate(const sf::Image& sourceImage, int numberSystem)
{
	int output = 0; //wynik w systemie dziesietnym
	std::string outputString = ""; //wynik w systemie danym przez uzytkownika

	std::vector<sf::Image> images = PixelTraversal::getImages(sourceImage);

	for (int i = 0; i < images.size(); i++)
	{
		images[i] = ResizeImage::resizeImageToSquare(images[i]);
		images[i] = ScaleImage::scaleImage(images[i], sf::Vector2i(TRAINED_IMAGE_WIDTH, TRAINED_IMAGE_HEIGHT) );

		output *= numberSystem; //mnozenie razy podstawa systemu liczbowego
		
		int evaluatedImageValue = evaluateImage(images[i]);
		
		if (evaluatedImageValue >= numberSystem)
			throw std::runtime_error("This is not a number in " + std::to_string(numberSystem) + " system");

		output += evaluatedImageValue;
		outputString += std::to_string( evaluatedImageValue );
	}

	return std::pair<std::string, int>(outputString, output);
}

void AI::loadModel(const std::string& path)
{
	torch::serialize::InputArchive input_archive;
	input_archive.load_from(path);
	model.load(input_archive);
	model.to(device);
}
