#pragma once
#include <argparse/argparse.hpp>
#include "SubCommand.h"

class HiddenSubCommand: public SubCommand
{
	std::vector<SubCommand*> subCommands;

public:
	HiddenSubCommand();
	void doCommand() override;
	~HiddenSubCommand();
};

