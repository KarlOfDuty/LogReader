#pragma once

#include <iostream>
#include "base_command.hpp"
#include "command_parser.hpp"
#include "../utils.hpp"
#include "../log_data.hpp"

class FilterCommand : public BaseCommand
{
public:
	void execute(std::vector<std::string> commandArguments) override;
private:
	void filterPhrase(const std::string& phrase);
	void filterLargerValue(const std::string& phrase);
	void filterSmallerValue(const std::string& phrase);
};
