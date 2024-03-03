#include "PixelTraversal.hpp"

std::vector<sf::Image> PixelTraversal::getImages(sf::Image image) {
	std::vector<sf::Image> images = std::vector<sf::Image>();

	for (int x = 0; x < image.getSize().x; x++) {
		for (int y = 0; y < image.getSize().y; y++) {
			//r=g=b
			if (image.getPixel(sf::Vector2u(x, y)).r != 0) {
				try {
					images.push_back(getSubImage(image, x, y));
				}
				catch (std::exception e) {
					std::cout<<e.what()<<std::endl;
				}
			}
		}
	}
	return images;
}

sf::Image PixelTraversal::getSubImage(sf::Image& image, int x, int y) {
	//3d vectors contains 2d position(x,y) and brightness(z) of the pixel, r=g=b
	std::vector<sf::Vector3i> pixels;
	std::vector<sf::Vector3i> checkedPixels;

	pixels.emplace_back(x, y, image.getPixel(sf::Vector2u(x, y)).r);
	image.setPixel(sf::Vector2u(x, y), sf::Color(0, 0, 0));

	sf::Vector2i bottomRight(0, 0);
	sf::Vector2i topLeft(x, y);

	while (pixels.size()) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (validPixel(image, pixels[0], i, j)) {
					pixels.emplace_back(pixels[0].x + i, pixels[0].y + j, image.getPixel(sf::Vector2u(pixels[0].x + i, pixels[0].y + j)).r);
					image.setPixel(sf::Vector2u(pixels[0].x + i, pixels[0].y + j), sf::Color(0, 0, 0));

					bottomRight.x = std::max(bottomRight.x, pixels[0].x + i);
					bottomRight.y = std::max(bottomRight.y, pixels[0].y + j);
					topLeft.x = std::min(topLeft.x, pixels[0].x + i);
					topLeft.y = std::min(topLeft.y, pixels[0].y + j);
				}
			}
		}
		checkedPixels.push_back(pixels[0]);
		pixels.erase(pixels.begin());
	}

	if (!validSubImage(checkedPixels)) 
		throw std::exception("Sub image not valid");
	
	return creteSubImage(checkedPixels, topLeft, bottomRight);
}

//it checks if pixel can be traversed
bool PixelTraversal::validPixel(const sf::Image& image, sf::Vector3i pixel, int dx, int dy) {
	//check if pixel is the same
	if (dx == 0 && dy == 0) return false;
	
	//check if pixel is out of bounds
	if (pixel.x + dx < 0 || pixel.x + dx >= image.getSize().x) return false;
	if (pixel.y + dy < 0 || pixel.y + dy >= image.getSize().y) return false;
	
	//check if pixel is black (we don't want to traverse black pixels)
	if (image.getPixel(sf::Vector2u(pixel.x + dx, pixel.y + dy)) == sf::Color(0, 0, 0)) return false;
	return true;
}

bool PixelTraversal::validSubImage(std::vector<sf::Vector3i> checkedPixels) {
	int check = 0;
	for (const sf::Vector3i pixel : checkedPixels) {
		//under pixel.z we store brightness of the pixel
		//if pixel is bright enough we count it
		if (pixel.z > PIXEL_MIN_BRIGHTNESS) check++;
	}

	if (check < MIN_PIXEL_IMAGE_COUNT) return false;
	return true;
}

sf::Image PixelTraversal::creteSubImage(const std::vector<sf::Vector3i>& checkedPixels, sf::Vector2i topLeft, sf::Vector2i bottomRight) {
	sf::Image subImage = sf::Image();

	//create subimage with size of the subimage and fill it with black color
	//we add 1 to the size becouse it's being substracted.
	subImage.create(sf::Vector2u(bottomRight.x - topLeft.x + 1, bottomRight.y - topLeft.y + 1), sf::Color(0, 0, 0));

	for (const sf::Vector3i pixel : checkedPixels) {
		subImage.setPixel(sf::Vector2u(pixel.x - topLeft.x, pixel.y - topLeft.y), sf::Color(pixel.z, pixel.z, pixel.z));
	}
	return subImage;
}