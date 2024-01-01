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

/// @brief function that provides division for sf::Vector2, helpful for scaling
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


/// @brief function that retrieves the directory of the executable, to get the path to the model
/// @return **std::string** - directory of the executable
inline std::string GetExecutableDirectory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(nullptr, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}