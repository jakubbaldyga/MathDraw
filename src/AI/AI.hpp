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

	AI();

	int evaluate(const sf::Image& sourceImage, bool isDebug = false);

	void loadModel(const std::string& path);
};
