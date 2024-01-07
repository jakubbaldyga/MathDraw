#include "Parser.hpp"
#include "RecogniseSubCommand/RecogniseSubCommand.hpp"
#include "HiddenSubCommands/HiddenSubCommand.hpp"

Parser::Parser(std::string programName, std::string programVersion): argparse::ArgumentParser(programName, programVersion)
{
	subCommands = std::vector<SubCommand*>();
	subCommands.push_back(new RecogniseSubCommand());
	subCommands.push_back(new HiddenSubCommands);
	
	for(auto subCommand : subCommands) {
		add_subparser(*subCommand);
	}
}

void Parser::parseArgs(int argc, char* argv[])
{
	try {
		ArgumentParser::parse_args(argc, argv);
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << *this;
		return;
	}

	for (auto subCommand : subCommands) {
		if (is_subcommand_used(*subCommand)) {
			subCommand->doCommand();
		}
	}
}

Parser::~Parser()
{
	for (auto subCommand : subCommands) {
		delete subCommand;
	}
	subCommands.clear();
	
}
