#include "SubCommand.hpp"

SubCommand::SubCommand(const std::string& name, const std::string& description) : argparse::ArgumentParser(name, "", argparse::default_arguments::help) {
	add_description(description);
}
