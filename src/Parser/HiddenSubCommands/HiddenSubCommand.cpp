#include "HiddenSubCommand.hpp"
#include "TraverseSubCommand/TraverseSubCommand.hpp"
#include "ResizeSubCommand/ResizeSubCommand.hpp"
#include "ScaleSubCommand/ScaleSubCommand.hpp"


HiddenSubCommands::HiddenSubCommands(): SubCommand("hidden", "Hidden subcommands for debug and testing")
{
	set_suppress(true);

	subCommands = std::vector<SubCommand*>();
	subCommands.push_back(new TraverseSubCommand());
	subCommands.push_back(new ResizeSubCommand());
	subCommands.push_back(new ScaleSubCommand());

	for (auto subCommand : subCommands) {
		add_subparser(*subCommand);
	}
}

void HiddenSubCommands::doCommand()
{
	for (auto subCommand : subCommands) {
		if (is_subcommand_used(*subCommand)) {
			subCommand->doCommand();
		}
	}
}

HiddenSubCommands::~HiddenSubCommands()
{
	for (auto subCommand : subCommands) {
		delete subCommand;
	}
	subCommands.clear();
}
