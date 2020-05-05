#include "logreader.hpp"

LogReader::LogReader()
{
	std::cout << "Fetching logs...\n";

	LogData::fileList = DirectoryReader::getFilePaths("logs/");

	if (LogData::fileList.empty())
	{
		std::cout << "No logs present in ./logs. Aborting...\n";
		return;
	}

	std::cout << "Done.\n";
	std::cout << "Reading logs...\n";
	readLogs();
	std::cout << LogData::logContents.size() << "\n";
	std::cout << LogData::logContents.back().size() << "\n";
	std::cout << "Done. Read " << LogData::logContents.back().size() << " rows.\n";
	while (true)
	{
		std::string input = {};

		std::cout << "> ";
		std::getline(std::cin, input);

		std::vector<std::string> commandArguments = CommandParser::parseCommandString(input);

		if (commandArguments.empty()) continue;

		switch (CommandParser::parseKeyword(extractFrontOrDefault(commandArguments)))
		{
			case Argument::PRINT:
				for (std::string& row : LogData::logContents.back())
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

void LogReader::readLogs()
{
	std::fstream file = std::fstream();
	LogData::logContents.emplace_back(std::vector<std::string>());
	for (std::string& fileName : LogData::fileList)
	{
		std::cout << " Reading " << fileName << "...\n";
		LogData::logContents.back().emplace_back("-- File: " + fileName + " --");
		file.open(fileName);
		do
		{
			LogData::logContents.back().emplace_back("");
		}
		while (std::getline(file, LogData::logContents.back().back()));
		file.close();
	}
}

void LogReader::undo()
{
	if (LogData::logContents.size() > 1)
	{
		LogData::logContents.pop_back();
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
	for (std::string& row : LogData::logContents.back())
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
