#include "ResizeImage.hpp"
#include "Utilties.hpp"

sf::Image ResizeImage::resizeImageToSquare(const sf::Image& image)
{
	if(image.getSize().x == image.getSize().y)
		return image;

	//we resize to the larger side of the image
	unsigned int maxDimension = std::max(image.getSize().x, image.getSize().y);
	return resizeImage(image, sf::Vector2u(maxDimension, maxDimension));
}

sf::Image ResizeImage::resizeImage(const sf::Image& image, sf::Vector2u targetDimensions)
{
	sf::Image outputImage;
	outputImage.create(sf::Vector2u(targetDimensions.x, targetDimensions.y), sf::Color(0, 0, 0));

	sf::Vector2u dimensionsDifference = getDimensionDifference(image.getSize(), targetDimensions);

	for (int i = 0; i < image.getSize().x; i++)
		for (int j = 0; j < image.getSize().y; j++)
			outputImage.setPixel(sf::Vector2u(i + dimensionsDifference.x, j + dimensionsDifference.y), image.getPixel(sf::Vector2u(i, j)));

	return outputImage;
}

sf::Vector2u ResizeImage::getDimensionDifference(sf::Vector2u currentDimensions, sf::Vector2u targetDimensions)
{
	sf::Vector2f dimensionsDifference = (targetDimensions - currentDimensions) / 2;
	return sf::Vector2u(dimensionsDifference.x, dimensionsDifference.y);
}
