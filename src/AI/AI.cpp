#include <torch/torch.h>
#include <SFML/Graphics.hpp>
#include "PixelTraversal/PixelTraversal.hpp"
#include "ScaleImage/ScaleImage.hpp"
#include "AI.hpp"

torch::Tensor AI::preprocessImage(const sf::Image& image, int x, int y)
{
	torch::Tensor imageTensor = torch::zeros({ 1, x, y }, torch::kFloat32);
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			//r=g=b
			imageTensor[0][i][j] = static_cast<float>(image.getPixel(j,i).r) / 255.f;
		}
	}

	// Tak zostal wyuczony ten model - przy tych parametrach
	imageTensor = (imageTensor - 0.1307) / 0.3081;
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
	torch::serialize::InputArchive input_archive;
	input_archive.load_from("model.pt");
	model.load(input_archive);
	model.to(device);
	
}

int AI::evaluate(const sf::Image& sourceImage, bool isDebug)
{
	int output = 0;
	std::vector<sf::Image> images = PixelTraversal::getImages(sourceImage);

	for (int i = 0; i < images.size(); i++)
	{
		images[i] = ScaleImage::scaleImage(images[i]);

		if(isDebug) images[i].saveToFile("image" + std::to_string(i) + ".png");

		output *= 10;
		output += evaluateImage(images[i]);
	}

	return output;
}
