#pragma once

#include <torch/torch.h>
#include <SFML/Graphics.hpp>
#include "Net/Net.hpp"

class AI
{
private:
	static const int TRAINED_IMAGE_WIDTH;
	static const int TRAINED_IMAGE_HEIGHT;
	static const double DEVIATION_BIAS;
	static const double DEVIATION_SCALE;

	static torch::Tensor preprocessImage(const sf::Image& image);

	int evaluateImage(const sf::Image& image);

	torch::Device device = torch::Device(torch::kCPU);
	Net model;


public:

	AI(const std::string& path);

	std::pair<std::string, int> evaluate(const sf::Image& sourceImage, int numberSystem);

	void loadModel(const std::string& path);
};
