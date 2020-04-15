#pragma once
#include <string>
#include <vector>

class BaseCommand
{
public:
	virtual ~BaseCommand() = default;

	virtual void execute(std::vector<std::string> commandArguments) = 0;
};
