#pragma once

#include <torch/torch.h>

struct Net : torch::nn::Module {
	Net();

	torch::Tensor forward(torch::Tensor x);

	torch::nn::Conv2d conv1;
	torch::nn::Conv2d conv2;
	torch::nn::Dropout2d conv2_drop;
	torch::nn::Linear fc1;
	torch::nn::Linear fc2;
};
