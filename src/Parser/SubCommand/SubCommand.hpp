#pragma once
#include <argparse/argparse.hpp>

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Abstract class for subcommands.
*/
class SubCommand : public argparse::ArgumentParser
{
	public:
	/// @brief Constructor, here will be added all the arguments
	/// @param name - name of the subcommand, used to call it from console
	/// @param description - description of the subcommand
	SubCommand(const std::string& name, const std::string& description );

	/// @brief function that executes the subcommand
	virtual void doCommand() = 0;
};