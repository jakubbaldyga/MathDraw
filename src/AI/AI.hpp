#pragma once
#include <torch/torch.h>
#include <SFML/Graphics.hpp>
#include "Net/Net.hpp"

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief The AI class responsible for evaluating images.
* \details **Description:**<br>
*		   Firstly it preprocesses the image(divide to digits and then scale).<br>
*		   Tensor is passed to the neural network and the result is returned.<br>
*		   Also loads trained model to neural network.	<br>
*/
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
	/// @brief Default constructor
	/// @param modelPath - path to the model to load
	/// @see loadModel()
	AI(const std::string& modelPath);

	 
	/// @brief Evaluates the image and returns the result.
	/// 
	/// @param sourceImage - image to evaluate
	/// @param numberSystem - number system to load the image in
	/// 
	/// @return	**string** - value in decimal system 
	/// @return **int** - value in decimal system
	std::pair<std::string, int> evaluate(const sf::Image& sourceImage, int numberSystem);

	/// @brief loads the trained model from the given path
	/// @param modelPath - path to the model to load
	void loadModel(const std::string& modelPath);
};
