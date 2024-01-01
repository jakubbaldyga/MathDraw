#include <iostream>
#include <argparse/argparse.hpp>
#include "Parser/Parser.h"

/**
* \author Jakub Ba³dyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Ba³dyga, MIT License
* \brief Main prgram function.
*/
int main(int argc, char* argv[])
{
	const std::string programName = "MathDraw";
	const std::string programVersion = "1.0.0";
	Parser parser(programName, programVersion);
	parser.parseArgs(argc, argv);
}
