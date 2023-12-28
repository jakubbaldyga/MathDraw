#include "HiddenSubCommand.h"
#include "RecogniseSubCommand.h"
#include "ScaleSubCommand.h"
HiddenSubCommand::HiddenSubCommand(): SubCommand("hidden", "Hidden subcommands for debug and testing")
{
	set_suppress(true);

	subCommands = std::vector<SubCommand*>();
	subCommands.push_back(new RecogniseSubCommand());
	subCommands.push_back(new ScaleSubCommand());

	for (auto subCommand : subCommands) {
		add_subparser(*subCommand);
	}
}

void HiddenSubCommand::doCommand()
{
	for (auto subCommand : subCommands) {
		if (is_subcommand_used(*subCommand)) {
			subCommand->doCommand();
		}
	}
}

HiddenSubCommand::~HiddenSubCommand()
{
	for (auto subCommand : subCommands) {
		delete subCommand;
	}
	subCommands.clear();
}
