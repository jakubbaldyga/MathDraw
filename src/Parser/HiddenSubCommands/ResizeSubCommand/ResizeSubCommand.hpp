#pragma once
#include "../../SubCommand/SubCommand.hpp"

class ResizeSubCommand : public SubCommand
{
public:
	ResizeSubCommand();

	void doCommand() override;
};