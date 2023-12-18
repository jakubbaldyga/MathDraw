#include "AI/AI.hpp"
#include <iostream>


int main()
{
	sf::Image sourceImage;
	if (!sourceImage.loadFromFile("image.png"))
		return -1;

	AI ai;
	std::cout<< "Wynik: "<< ai.evaluate(sourceImage, false) << std::endl;
	std::cout << "Aby zakonczyc wcisnij enter...\n";
	std::cin.get();
	return 0;
}