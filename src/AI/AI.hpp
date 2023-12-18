#pragma once

#include <torch/torch.h>
#include <SFML/Graphics.hpp>
#include "Net/Net.hpp"

class AI
{
private:

	static float getImagePixel(const sf::Image& image, int x, int y);

	static torch::Tensor preprocessImage(const sf::Image& image, int x = 28, int y = 28);

	int evaluateImage(const sf::Image& image);

	torch::Device device = torch::Device(torch::kCPU);
	Net model;


public:

	AI();

	int evaluate(const sf::Image& sourceImage, bool isDebug = false);
};
