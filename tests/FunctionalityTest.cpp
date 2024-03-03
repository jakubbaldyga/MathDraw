#include <catch2/catch_test_macros.hpp>
#include "../src/Utilities/Strings.hpp"
#include "../src/Utilities//Utilties.hpp"
#include <SFML/System/Vector2.hpp>
#include "../src/AI/PixelTraversal/PixelTraversal.hpp"
#include "../src/AI/ScaleImage/ScaleImage.hpp"
#include "../src/AI/AI.hpp"

/**
* \author Jakub Baldyga
* \date 17/02/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Test class for functionallity testing.
*/

template <class Function, class ... Args>
bool checkThrows(Function&& func) {
	try {
		func();
	}
	catch (...) {
		return true;
	}
	return false;
}


TEST_CASE("AI check") {
	sf::Image image;
	image.loadFromFile("res/test/empty.png");
	AI ai("res/model.pt");

	auto func = std::bind(&AI::evaluate, ai, image, 10);
	REQUIRE(checkThrows(func) == true);

	image.loadFromFile("res/test/one.png");
	REQUIRE(ai.evaluate(image, 10).second == 1);

	image.loadFromFile("res/test/two.png");
	REQUIRE(ai.evaluate(image, 10).second == 2);

	image.loadFromFile("res/test/three.png");
	REQUIRE(ai.evaluate(image, 10).second == 3);

	image.loadFromFile("res/test/four.png");
	REQUIRE(ai.evaluate(image, 10).second == 4);

	image.loadFromFile("res/test/12.png");
	REQUIRE(ai.evaluate(image, 10).first == "12");
	REQUIRE(ai.evaluate(image, 10).second == 12);
	
	auto func2 = std::bind(&AI::evaluate, ai, image, 2);
	REQUIRE(checkThrows(func2) == true);
}

TEST_CASE("Algorithms check") {
	sf::Image image;
	image.loadFromFile("res/test/empty.png");

	REQUIRE(PixelTraversal::getImages(image).size() == 0);

	image.loadFromFile("res/test/12.png");

	auto result = PixelTraversal::getImages(image);
	sf::Image im1, im2;
	im1.loadFromFile("res/test/traversedImage0.png");
	im2.loadFromFile("res/test/traversedImage1.png");

	REQUIRE(result.size() == 2);
	REQUIRE(result[0] == im1);
	REQUIRE(result[1] == im2);

	sf::Image scaledImage = ScaleImage::scaleImage(image, sf::Vector2i(10, 10));
	im1.loadFromFile("res/test/scaledImage.png");
	REQUIRE(scaledImage == im1);
}
