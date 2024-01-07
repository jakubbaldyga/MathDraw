#pragma once

#include <string>

/**
* \file Strings.hpp
* \author Jakub Baldyga
* \date 7/01/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Strings file. Contains most strings used in the program.
*/
class Strings {
public:
	static const std::string PROGRAM_NAME;
	static const std::string PROGRAM_VERSION;

	//commands
	static const std::string RECOGNISE_COMMAND_NAME;
	static const std::string RECOGNISE_COMMAND_DESCRRIPTION;
	
	static const std::string HIDDEN_COMMAND_NAME;
	static const std::string HIDDEN_COMMAND_DESCRRIPTION;

	static const std::string SCALE_COMMAND_NAME;
	static const std::string SCALE_COMMAND_DESCRIPTION;
	
	static const std::string TRAVERSE_COMMAND_NAME;
	static const std::string TRAVERSE_COMMAND_DESCRIPTION;

	static const std::string RESIZE_COMMAND_NAME;
	static const std::string RESIZE_COMMAND_DESCRRIPTION;

	//specify
	static const std::string SPECIFY_IMAGE_FILE;
	static const std::string SPECIFY_MODEL_FILE;
	static const std::string SPECIFY_OUTPUT_FILE;
	static const std::string SPECIFY_NUMBER_BASE_SYSTEM;

	static const std::string SPECIFY_WIDTH;
	static const std::string SPECIFY_HEIGHT;

};