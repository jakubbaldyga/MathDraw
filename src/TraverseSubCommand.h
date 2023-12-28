#pragma once
#include "SubCommand.h"
class TraverseSubCommand: public SubCommand
{
public:
	TraverseSubCommand();

	void doCommand() override;

};

