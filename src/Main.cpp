#include <iostream>
#include <argparse/argparse.hpp>
#include "Parser.h"

int main(int argc, char* argv[])
{
	const std::string programName = "MathDraw";
	const std::string programVersion = "1.0.0";

	Parser parser(programName, programVersion);
	parser.parse_args(argc, argv);
}