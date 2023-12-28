#pragma once
#include "SubCommand.h"

class ScaleSubCommand: public SubCommand
{
public:

	ScaleSubCommand();

	void doCommand() override;
};

