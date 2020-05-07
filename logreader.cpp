#include "logreader.hpp"

LogReader::LogReader()
{
	std::cout << "Fetching logs...\n";

	if(!Filesystem::initialize("logs/"))
	{
		return;
	}

#ifndef _WIN32
	system("clear");
#else
	system("CLS");
#endif

	std::cout << "|###########################################################|\n" 
	          << "                    LogReader " << VERSION << "\n"
			  << "|###########################################################|\n";
	std::cout << "Done. Read " << Filesystem::logContents.back().size() << " rows.\n";
	while (true)
	{
		std::string input = {};

		std::cout << "> ";
		std::getline(std::cin, input);

		std::vector<std::string> commandArguments = CommandParser::parseCommandString(input);

		if (commandArguments.empty()) continue;

		switch (CommandParser::parseKeyword(Utils::extractFrontOrDefault(commandArguments)))
		{
			case Argument::PRINT:
				for (std::string& row : Filesystem::logContents.back())
				{
					std::cout << row << "\n";
				}
				break;
			case Argument::SAVE:
				saveToFile();
				break;
			case Argument::UNDO:
				undo();
				break;
			case Argument::FILTER:
				filterCommand.execute(commandArguments);
				break;
			case Argument::HELP:
				std::cout << HELP_MESSAGE;
				break;
			case Argument::QUIT:
				return;
			default:
				std::cout << "Invalid command. Use 'help' for a full list of commands.\n";
				break;
		}
	}
}

void LogReader::undo()
{
	if (Filesystem::logContents.size() > 1)
	{
		Filesystem::logContents.pop_back();
		std::cout << "Last action undone.\n";
	}
	else
	{
		std::cout << "No actions left to undo.\n";
	}
}

void LogReader::saveToFile()
{
	std::cout << "Saving log file...\n";
	std::string outString;
	for (std::string& row : Filesystem::logContents.back())
	{
		outString.append(row);
		outString.append("\n");
	}

	std::ofstream fs = std::ofstream("output.log");
	if (fs.is_open())
	{
		fs << outString;
		fs.close();
		std::cout << "Log saved as 'output.log'.\n";
	}
	else
	{
		std::cout << "Error: Could not save 'output.log'.\n";
	}
}
