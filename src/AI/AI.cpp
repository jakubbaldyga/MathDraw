#include <torch/torch.h>
#include <SFML/Graphics.hpp>
#include "PixelTraversal/PixelTraversal.hpp"
#include "ScaleImage/ScaleImage.hpp"
#include "AI.hpp"

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
	model.eval();
	auto pred = output.argmax(1);
	return pred.item<int>();
}

AI::AI()
{
	torch::manual_seed(0);
	device = torch::Device(torch::kCPU);
	loadModel("model.pt");
}

int AI::evaluate(const sf::Image& sourceImage, bool isDebug)
{
	int output = 0;
	std::vector<sf::Image> images = PixelTraversal::getImages(sourceImage);

	for (int i = 0; i < images.size(); i++)
	{
		images[i] = ScaleImage::scaleImage(images[i], TRAINED_IMAGE_WIDTH, TRAINED_IMAGE_HEIGHT);

		if(isDebug) images[i].saveToFile("image" + std::to_string(i) + ".png");

		output *= 10; //mnozenie razy podstawa systemu liczbowego(10)
		output += evaluateImage(images[i]);
	}

	return output;
}

void AI::loadModel(const std::string& path)
{
	torch::serialize::InputArchive input_archive;
	input_archive.load_from(path);
	model.load(input_archive);
	model.to(device);
}
