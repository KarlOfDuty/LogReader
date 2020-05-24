#pragma once

#include "base_command.hpp"
#include "../utils.hpp"

class SaveCommand : public BaseCommand
{
public:
	void execute(std::vector<std::string> commandArguments) override;
};
