#include "command_parser.hpp"

std::vector<std::string> CommandParser::parseCommandString(std::string input)
{
	std::vector<std::string> commandArguments = {};

	std::stringstream ss(input);

	std::string arg;
	while (ss.good())
	{
		ss >> arg;
		commandArguments.push_back(arg);
	}

	return commandArguments;
}

Argument CommandParser::parseKeyword(std::string argument)
{
	if (argument == "print") return Argument::PRINT;
	if (argument == "save") return Argument::SAVE;
	if (argument == "undo") return Argument::UNDO;
	if (argument == "filter") return Argument::FILTER;
	if (argument == "phrase") return Argument::PHRASE;
	if (argument == "value") return Argument::VALUE;
	if (argument == "larger") return Argument::LARGER;
	if (argument == "smaller") return Argument::SMALLER;
	if (argument == "help") return Argument::HELP;
	if (argument == "quit") return Argument::QUIT;
	return Argument::USER_INPUT;
}
