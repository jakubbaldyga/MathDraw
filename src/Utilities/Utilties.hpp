#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Windows.h"
/**
* \file Utilties.hpp
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Utilities file.
*/

/// @brief operator / that provides division for sf::Vector2 and sf::Vector2
/// @param a - first vector
/// @param b - second vector
/// @return  **sf::Vector2f** - result of division a/b
template<typename T, typename U>
sf::Vector2f operator/(sf::Vector2<T> a, sf::Vector2<U> b)
{
	sf::Vector2f result;
	result.x = (float)a.x / (float)b.x;
	result.y = (float)a.y / (float)b.y;
	return result;
}

/// @brief operator / that provides division for sf::Vector2 and number
/// @param a - vector
/// @param b - number
/// @return  **sf::Vector2f** - result of division a/b
template<typename T, typename U>
sf::Vector2f operator/(sf::Vector2<T> a, U b)
{
	sf::Vector2f result;
	result.x = (float)a.x / (float)b;
	result.y = (float)a.y / (float)b;
	return result;
}

/// @brief operator * that provides multiplication for sf::Vector2 and sf::Vector2
/// @param a - first vector
/// @param b - second vector
/// @return  **sf::Vector2f** - result of multiplication a*b
template<typename T, typename U>
sf::Vector2f operator*(sf::Vector2<T> a, sf::Vector2<U> b)
{
	sf::Vector2f result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	return result;
}

/// @brief operator == that provides comparison for sf::Image
/// @param img1 - first image
/// @param img2 - second image
/// return **bool** - result of comparison. True if images are the same, false otherwise
inline bool operator==(sf::Image& img1, sf::Image& img2) {

	if (img1.getSize() != img2.getSize()) return false;

	for (int i = 0; i < img1.getSize().x; i++) {
		for (int j = 0; j < img1.getSize().y; j++) {
			if (img1.getPixel(sf::Vector2u(i, j)) != img2.getPixel(sf::Vector2u(i, j))) return false;
		}
	}
	return true;
}

/// @brief function that retrieves the directory of the executable, works only on windows
/// @return **std::string** - directory of the executable
inline std::string GetExecutableDirectory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(nullptr, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}