#pragma once

#include <iostream>
#include "base_command.hpp"
#include "command_parser.hpp"
#include "../utils.hpp"

class FilterCommand : public BaseCommand
{
public:
	void execute(std::vector<std::string> commandArguments) override;
private:
	static void filterPhrase(const std::string& phrase);
	static void filterLargerValue(const std::string& phrase);
	static void filterSmallerValue(const std::string& phrase);
};
