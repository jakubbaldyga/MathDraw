#pragma once
#include <argparse/argparse.hpp>

class SubCommand : public argparse::ArgumentParser
{
	public:
	SubCommand(const std::string& name, const std::string& description );
	virtual void doCommand() = 0;
};