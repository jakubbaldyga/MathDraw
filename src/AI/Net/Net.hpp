#pragma once

#include <torch/torch.h>


/**
* \author Jakub Bałdyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Bałdyga, MIT License
* \brief Neural network designed to recognise images.
* \details This is a neural network that recognises digit on the preapred image.
*/
struct Net : torch::nn::Module {
	/// @brief Default constructor
	Net();

	/// @brief evaluates the image and returns the result.
	/// @param imageTensor - image to evaluate in Tensor data type
	/// @return **Tensor** - value in decimal system
	torch::Tensor forward(torch::Tensor imageTensor);

	/// @brief convolutional layer 1
	torch::nn::Conv2d conv1;
	/// convolutional layer 2
	torch::nn::Conv2d conv2;

	/// @brief dropout layer
	torch::nn::Dropout2d conv2_drop;

	/// @brief fully connected layer 1
	torch::nn::Linear fc1;

	/// @brief fully connected layer 2
	torch::nn::Linear fc2;
};
