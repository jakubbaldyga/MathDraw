#include "HiddenSubCommand.hpp"
#include "TraverseSubCommand/TraverseSubCommand.hpp"
#include "ResizeSubCommand/ResizeSubCommand.hpp"
#include "ScaleSubCommand/ScaleSubCommand.hpp"
#include "Strings.hpp"

HiddenSubCommands::HiddenSubCommands(): SubCommand(Strings::HIDDEN_COMMAND_NAME, Strings::HIDDEN_COMMAND_DESCRRIPTION) {
	set_suppress(true);

	subCommands = std::vector<std::unique_ptr<SubCommand>>();
	subCommands.push_back(std::make_unique<TraverseSubCommand>());
	subCommands.push_back(std::make_unique<ResizeSubCommand>());
	subCommands.push_back(std::make_unique<ScaleSubCommand>());

	for (auto &subCommand : subCommands) {
		add_subparser(*subCommand);
	}
}

void HiddenSubCommands::doCommand() {
	for (auto & subCommand : subCommands) {
		if (is_subcommand_used(*subCommand)) {
			subCommand->doCommand();
		}
	}
}