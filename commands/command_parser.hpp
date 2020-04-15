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
	static std::vector<std::string> parseCommandString(std::string input);

	static Argument parseKeyword(std::string argument);
};
