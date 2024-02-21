#include "PixelTraversal.hpp"

std::vector<sf::Image> PixelTraversal::getImages(sf::Image image)
{
	std::vector<sf::Image> images = std::vector<sf::Image>();

	for (int x = 0; x < image.getSize().x; x++) {
		for (int y = 0; y < image.getSize().y; y++) {
			if (image.getPixel(sf::Vector2u(x, y)).r != 0) {
				try {
					images.push_back(getSubImage(image, x, y));
				}
				catch (std::exception e) {
					continue;
				}
			}
		}
	}
	return images;
}

sf::Image PixelTraversal::getSubImage(sf::Image& image, int x, int y)
{
	std::vector<sf::Vector3i> pixels;
	std::vector<sf::Vector3i> checkedPixels;

	pixels.emplace_back(x, y, image.getPixel(sf::Vector2u(x, y)).r);
	image.setPixel(sf::Vector2u(x, y), sf::Color(0, 0, 0));

	sf::Vector2i size(0, 0);
	sf::Vector2i topLeft(x, y);

	do
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!validPixel(image, pixels[0], i, j)) continue;

				pixels.emplace_back(pixels[0].x + i, pixels[0].y + j, image.getPixel(sf::Vector2u(pixels[0].x + i, pixels[0].y + j)).r);
				image.setPixel(sf::Vector2u(pixels[0].x + i, pixels[0].y + j), sf::Color(0, 0, 0));

				size.x = std::max(size.x, pixels[0].x + i);
				size.y = std::max(size.y, pixels[0].y + j);
				topLeft.x = std::min(topLeft.x, pixels[0].x + i);
				topLeft.y = std::min(topLeft.y, pixels[0].y + j);
			}
		}
		checkedPixels.push_back(pixels[0]);
		pixels.erase(pixels.begin());
	} while (pixels.size());

	if (!validSubImage(checkedPixels))
		throw std::exception("Sub image not valid");

	return creteSubImage(checkedPixels, topLeft, size);
}

bool PixelTraversal::validPixel(const sf::Image& image, sf::Vector3i pixel, int dx, int dy)
{
	if (dx == 0 && dy == 0) return false;
	if (pixel.x + dx < 0 || pixel.x + dx >= image.getSize().x) return false;
	if (pixel.y + dy < 0 || pixel.y + dy >= image.getSize().y) return false;
	if (image.getPixel(sf::Vector2u(pixel.x + dx, pixel.y + dy)) == sf::Color(0, 0, 0)) return false;
	return true;
}

bool PixelTraversal::validSubImage(std::vector<sf::Vector3i> checkedPixels)
{
	int check = 0;
	for (const sf::Vector3i pixel : checkedPixels)
	{
		if (pixel.z > 150) check++;
	}

	if (check < 10) return false;
	return true;
}

sf::Image PixelTraversal::creteSubImage(const std::vector<sf::Vector3i>& checkedPixels, sf::Vector2i topLeft, sf::Vector2i size)
{
	sf::Image subImage = sf::Image();
	subImage.create(sf::Vector2u(size.x + 1 - topLeft.x, size.y + 1 - topLeft.y), sf::Color(0, 0, 0));

	for (const sf::Vector3i pixel : checkedPixels)
	{
		subImage.setPixel(sf::Vector2u(pixel.x - topLeft.x, pixel.y - topLeft.y), sf::Color(pixel.z, pixel.z, pixel.z));
	}
	return subImage;
}