#pragma once
#include <argparse/argparse.hpp>
#include <vector>
#include "SubCommand.h"
class Parser: public argparse::ArgumentParser
{
	std::vector<SubCommand*> subCommands;

public:
	Parser(std::string programName, std::string programVersion);
	void parse_args(int argc, char* argv[]);
	~Parser();
};