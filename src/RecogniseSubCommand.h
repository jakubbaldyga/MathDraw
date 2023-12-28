#pragma once
#include "SubCommand.h"
class RecogniseSubCommand : public SubCommand
{
	public:
	
	RecogniseSubCommand();

	void doCommand() override;

};