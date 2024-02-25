#pragma once
#include <argparse/argparse.hpp>
#include <vector>
#include "SubCommand/SubCommand.hpp"
#include <memory>

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Main parser class.
* \details **Description:**<br>
*		  Call with --help for more details and available commands<br>
*		  \code{.bash}
*		  MathDraw --help
*		  \endcode
*/
class Parser: public argparse::ArgumentParser {
	std::vector<std::unique_ptr<SubCommand>> subCommands;

public:
	/// @brief Default constructor
	/// @param programName - name of the program
	/// @param programVersion - version of the program
	Parser(std::string programName, std::string programVersion);

	///@brief parses the arguments, and calls the appropriate subcommand
	/// @param argc, argv - arguments from main function
	void parseArgs(int argc, char* argv[]);
};