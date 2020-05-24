#include "save_command.hpp"

void SaveCommand::execute(std::vector<std::string> commandArguments)
{
	std::cout << "Saving log file...\n";

	std::string fileName = "output";
	std::string argument = Utils::extractFrontOrDefault(commandArguments);

	if (!Utils::isEmptyOrWhitespace(argument))
	{
		fileName = argument;
	}

	std::string outString;
	for (std::string& row : Filesystem::logContents.back())
	{
		outString.append(row);
		outString.append("\n");
	}

	std::ofstream fs = std::ofstream("./output/" + fileName + ".log");
	if (fs.is_open())
	{
		fs << outString;
		fs.close();
		std::cout << "Log saved as './output/" << fileName << ".log'.\n";
	}
	else
	{
		std::cout << "Error: Could not save './output/" << fileName << ".log'.\n";
	}
}