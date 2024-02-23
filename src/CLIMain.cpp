#include <iostream>
#include <argparse/argparse.hpp>
#include "Parser/Parser.hpp"
#include "Strings.hpp"
/**
* \author Jakub Ba�dyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Ba�dyga, MIT License
* \brief Main prgram function of the command line interface.
*/
int main(int argc, char* argv[])
{
	Parser parser(Strings::PROGRAM_NAME, Strings::PROGRAM_VERSION);
	parser.parseArgs(argc, argv);
}
