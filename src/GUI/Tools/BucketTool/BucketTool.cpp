#include "BucketTool.hpp"
#include "PixelTraversal/PixelTraversal.hpp"

bool BucketTool::validPixel(const sf::Image& image, sf::Vector3i pixel, int dx, int dy)
{
	if (dx == 0 && dy == 0) return false;
	if (pixel.x + dx < 0 || pixel.x + dx >= image.getSize().x) return false;
	if (pixel.y + dy < 0 || pixel.y + dy >= image.getSize().y) return false;
	if (image.getPixel(sf::Vector2u(pixel.x + dx, pixel.y + dy)) == sf::Color(0, 0, 0)) return false;
	return true;
}

BucketTool::BucketTool(std::shared_ptr<ContentImage> contentImage) : Tool(contentImage) {}

void BucketTool::onMousePressed(sf::Vector2i position)
{
	//retrieve the clicked pixel
	sf::Vector2u pos = sf::Vector2u(position.x - contentImage->getPosition().x, position.y - contentImage->getPosition().y);
	pos.x /= contentImage->getScale().x;
	pos.y /= contentImage->getScale().y;

	sf::Image image = contentImage->getImage();

	//if the pixel is black there is nothing to fill
	if (image.getPixel(sf::Vector2u(pos.x, pos.y)) == sf::Color(0, 0, 0)) return;

	//now we traverse the image and fill the area
	std::vector<sf::Vector3i> pixels;

	//add the first pixel
	pixels.emplace_back(pos.x, pos.y, image.getPixel(sf::Vector2u(pos.x, pos.y)).r);
	
	while (pixels.size()) {
		//we add the pixels around the current pixel
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if (validPixel(image, pixels[0], x, y)) {
					pixels.emplace_back(pixels[0].x + x, pixels[0].y + y, image.getPixel(sf::Vector2u(pixels[0].x + x, pixels[0].y + y)).r);
					image.setPixel(sf::Vector2u(pixels[0].x + x, pixels[0].y + y), sf::Color(0, 0, 0));
				}
			}
		}
		//we set the pixel to black so we don't traverse it again
		contentImage->setPixel(sf::Vector2u(pixels[0].x, pixels[0].y), sf::Color(0, 0, 0));
		pixels.erase(pixels.begin());
	};

	contentImage->updateTexture();
}

//we don't need these functions
void BucketTool::onMouseReleased() {}

void BucketTool::onMouseMoved(sf::Vector2i position) {}