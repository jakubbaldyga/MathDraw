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

BucketTool::BucketTool(ContentImage* contentImage) : Tool(contentImage) {}

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
	
	do
	{
		//we add the pixels around the current pixel
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!validPixel(image, pixels[0], i, j)) continue;

				pixels.emplace_back(pixels[0].x + i, pixels[0].y + j, image.getPixel(sf::Vector2u(pixels[0].x + i, pixels[0].y + j)).r);
				image.setPixel(sf::Vector2u(pixels[0].x + i, pixels[0].y + j), sf::Color(0, 0, 0));
			}
		}
		//we set the pixel to black so we don't traverse it again
		contentImage->setPixel(sf::Vector2u(pixels[0].x, pixels[0].y), sf::Color(0, 0, 0));
		pixels.erase(pixels.begin());
	} while (pixels.size());

	contentImage->updateTexture();
}

//we don't need these functions
void BucketTool::onMouseReleased() {}

void BucketTool::onMouseMoved(sf::Vector2i position) {}