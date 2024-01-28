#include <catch2/catch_test_macros.hpp>
#include "../src/Utilities/Strings.hpp"
#include <SFML/System/Vector2.hpp>
#include "../src/Utilities/Utilties.hpp"
#include "../src/AI/PixelTraversal/PixelTraversal.hpp"
#include "../src/AI/AI.hpp"

class TestClass {
public:
    bool validPixel(const sf::Image& image, sf::Vector3i pixel, int dx, int dy) {
		return PixelTraversal::validPixel(image, pixel, dx, dy);
	}

    bool validSubImage(std::vector<sf::Vector3i> checkedPixels) {
        return PixelTraversal::validSubImage(checkedPixels);
    }

    int getAITrainedImageWidth() {
		return AI::TRAINED_IMAGE_WIDTH;
	}

    int getAITrainedImageHeight() {
		return AI::TRAINED_IMAGE_HEIGHT;
	}

    double getAIDeviationBias() {
		return AI::DEVIATION_BIAS;
	}

    double getAIDeviationScale() {
		return AI::DEVIATION_SCALE;
    }

};

TEST_CASE("Strings check") {

    REQUIRE(Strings::PROGRAM_NAME == "MathDraw");
    REQUIRE(Strings::PROGRAM_VERSION == "1.0.0");

    REQUIRE(Strings::RECOGNISE_COMMAND_NAME == "recognise");
    REQUIRE(Strings::RECOGNISE_COMMAND_DESCRRIPTION == "Recognise number from the image");

    REQUIRE(Strings::HIDDEN_COMMAND_NAME == "hidden");
    REQUIRE(Strings::HIDDEN_COMMAND_DESCRRIPTION == "Hidden subcommands for debug and testing");

    REQUIRE(Strings::SCALE_COMMAND_NAME == "scale");

    REQUIRE(Strings::SCALE_COMMAND_DESCRIPTION == "Scale the image");

    REQUIRE(Strings::TRAVERSE_COMMAND_NAME == "traverse");
    REQUIRE(Strings::TRAVERSE_COMMAND_DESCRIPTION == "Traverse the image");

    REQUIRE(Strings::RESIZE_COMMAND_NAME == "resize");
    REQUIRE(Strings::RESIZE_COMMAND_DESCRRIPTION == "Resize the image");

    REQUIRE(Strings::SPECIFY_IMAGE_FILE == "Specify image file");
    REQUIRE(Strings::SPECIFY_MODEL_FILE == "Specify model file");
    REQUIRE(Strings::SPECIFY_OUTPUT_FILE == "Specify output file");
    REQUIRE(Strings::SPECIFY_NUMBER_BASE_SYSTEM == "Specify number base system");

    REQUIRE(Strings::SPECIFY_WIDTH == "Specify width");
    REQUIRE(Strings::SPECIFY_HEIGHT == "Specify height");
}

TEST_CASE("Vector division check") {
    sf::Vector2i a(7, 10);
    sf::Vector2i b(8, 2);
    sf::Vector2f result = a / b;
    REQUIRE(result.x == 0.875);
    REQUIRE(result.y == 5);
}

TEST_CASE("pixel traversal validPixel check") {
    sf::Image image;
    image.create(sf::Vector2u(10, 10), sf::Color::Black);
    image.setPixel(sf::Vector2u(5, 5), sf::Color::White);
    TestClass testClass;

    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(0, 0, 0), 10, 10));
    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(0, 0, 0), 0, -1));
    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(0, 0, 0), -1, 0));
    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(9, 9, 0), 1, 0));
    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(9, 9, 0), 0, 1));
    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(0, 0, 0), 0,0));
    REQUIRE_FALSE(testClass.validPixel(image, sf::Vector3i(5, 5, 0), 0, 0));
    
    REQUIRE(testClass.validPixel(image, sf::Vector3i(4, 4, 0), 1, 1));
    REQUIRE(testClass.validPixel(image, sf::Vector3i(6, 6, 0), -1, -1));
}

TEST_CASE("PixelTraversalValidSubImageCheck") {
    TestClass testClass;
	std::vector<sf::Vector3i> checkedPixels;
	REQUIRE_FALSE(testClass.validSubImage(checkedPixels));

	checkedPixels.emplace_back(0, 0, 250);
	checkedPixels.emplace_back(1, 0, 250);
	checkedPixels.emplace_back(2, 0, 250);
	checkedPixels.emplace_back(3, 0, 250);
	checkedPixels.emplace_back(4, 0, 250);
	checkedPixels.emplace_back(5, 0, 250);
	checkedPixels.emplace_back(6, 0, 250);
	checkedPixels.emplace_back(7, 0, 250);
	checkedPixels.emplace_back(8, 0, 250);
	checkedPixels.emplace_back(9, 0, 100);
	REQUIRE_FALSE(testClass.validSubImage(checkedPixels));
    
    checkedPixels.emplace_back(10, 0, 250);
    REQUIRE(testClass.validSubImage(checkedPixels));
}

TEST_CASE("AI const values check") {
   TestClass testClass;

   REQUIRE(testClass.getAITrainedImageWidth() == 28);
   REQUIRE(testClass.getAITrainedImageHeight() == 28);
   REQUIRE(testClass.getAIDeviationBias() == 0.1307);
   REQUIRE(testClass.getAIDeviationScale() == 1/0.3081);
}