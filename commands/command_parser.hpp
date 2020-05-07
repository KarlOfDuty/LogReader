#pragma once

#include <string>
#include <vector>
#include <sstream>

enum class Argument : short
{
	PRINT,
	SAVE,
	UNDO,
	FILTER,
	// Filter sub-commands
	PHRASE,
	VALUE,
	LARGER,
	SMALLER,
	//
	HELP,
	QUIT,
	USER_INPUT
};

class CommandParser
{
public:
	static std::vector<std::string> parseCommandString(const std::string& input)
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

	static Argument parseKeyword(const std::string& argument)
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
		if (argument == "exit") return Argument::QUIT;
		return Argument::USER_INPUT;
	}
};
