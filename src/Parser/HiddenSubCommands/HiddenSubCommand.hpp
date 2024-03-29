#pragma once
#include <argparse/argparse.hpp>
#include <memory>
#include "../SubCommand/SubCommand.hpp"

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Hidden sub commands to call from console.
* \details **Description:**<br>
*		  Gate from which all hidden subcommands can be called<br>
*		  Should be used for testing<br>
*		  Call with --help to see all available hidden commands<br>
*		  \code{.bash}
*		  MathDraw hidden --help
*		  \endcode
*/
class HiddenSubCommands: public SubCommand
{
	std::vector<std::unique_ptr<SubCommand>> subCommands;

public:
	/// @brief Default constructor
	HiddenSubCommands();
	
	/// @brief selects subcommand to call
	void doCommand() override;
};

