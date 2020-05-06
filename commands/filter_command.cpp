#include "filter_command.hpp"

void FilterCommand::execute(std::vector<std::string> commandArguments)
{
	switch (CommandParser::parseKeyword(Utils::extractFrontOrDefault(commandArguments)))
	{
		case Argument::PHRASE:
		{
			// Put the rest of the command into a single string to search for
			std::string phrase = {};
			while (!commandArguments.empty())
			{
				phrase.append(Utils::extractFrontOrDefault(commandArguments));
				phrase.append(" ");
			}

			if (phrase.empty())
			{
				std::cout << "No search term provided.\n";
				return;
			}

			phrase.erase(phrase.end() - 1);
			filterPhrase(phrase);
			break;
		}
		case Argument::VALUE:
		{
			switch (CommandParser::parseKeyword(Utils::extractFrontOrDefault(commandArguments)))
			{
				case Argument::LARGER:
					filterLargerValue(Utils::extractFrontOrDefault(commandArguments));
					break;
				case Argument::SMALLER:
					filterSmallerValue(Utils::extractFrontOrDefault(commandArguments));
					break;
				default:
					std::cout << "Invalid sub-command. Use 'help' for a full list of commands.\n";
					break;
			}
			break;
		}
		default:
			std::cout << "Invalid sub-command. Use 'help' for a full list of commands.\n";
			break;
	}
}

void FilterCommand::filterPhrase(const std::string& phrase)
{
	std::vector<std::string> matchingLines = {};

	std::cout << "Filtering to lines containing the phrase: '" << phrase << "'\n";
	if (phrase.empty())
	{
		std::cout << "No phrase supplied.\n";
		return;
	}

	unsigned long long debugCounter = 0;
	std::cout << LogData::logContents.size();
	for (std::string& row : LogData::logContents.back())
	{
		if (row.find(phrase) != std::string::npos || Utils::isProtectedLine(row))
		{
			matchingLines.push_back(row);
		}
		debugCounter++;
		if (!(debugCounter % 10000))
		{
			std::cout << "Processed " << debugCounter << " rows. " << Utils::subtractTitles(matchingLines.size()) << " rows corresponding to the filter found.\n";
		}
	}
	std::cout << "Done. " << debugCounter << " rows searched, " << Utils::subtractTitles(matchingLines.size()) << " matches found.\n";
	LogData::logContents.push_back(matchingLines);
}

void FilterCommand::filterLargerValue(const std::string& phrase)
{
	std::vector<std::string> matchingLines = {};

	float inputValue = std::strtof(phrase.c_str(), nullptr);

	int debugCounter = 0;
	for (std::string& row : LogData::logContents.back())
	{
		std::stringstream ss = std::stringstream();
		std::string word = "";
		ss << row;
		bool found = Utils::isProtectedLine(row);
		while (ss && !found)
		{
			ss >> word;
			if (Utils::isNumber(word) && std::strtof(word.c_str(), nullptr) >= inputValue)
			{
				std::cout << word << "|" << std::strtof(word.c_str(), nullptr) << "\n";
				found = true;
			}
		}

		debugCounter++;
		if (!(debugCounter % 10000))
		{
			size_t foundRows = Utils::subtractTitles(matchingLines.size());
			std::cout << "Processed " << debugCounter << " rows. " << foundRows << " rows corresponding to the filter found. \n";
		}
		if (found)
		{
			matchingLines.push_back(row);
		}
	}
	std::cout << "Filtered to only values higher than or equal to " << inputValue << ".\n";
	std::cout << debugCounter << " rows searched, " << Utils::subtractTitles(matchingLines.size()) << " matches found.\n";
	LogData::logContents.push_back(matchingLines);
}

void FilterCommand::filterSmallerValue(const std::string& phrase)
{
	std::vector<std::string> matchingLines = {};

	float inputValue = std::strtof(phrase.c_str(), nullptr);

	int debugCounter = 0;
	for (std::string& row : LogData::logContents.back())
	{
		std::stringstream ss = std::stringstream();

		ss << row;
		bool found = Utils::isProtectedLine(row); // Always retain log file titles

		std::string word = {};
		while (ss && !found)
		{
			ss >> word;
			if (Utils::isNumber(word) && std::strtof(word.c_str(), nullptr) <= inputValue)
			{
				found = true;
			}
		}
		debugCounter++;
		if (!(debugCounter % 10000))
		{
			std::cout << "Processed " << debugCounter << " rows. " << Utils::subtractTitles(matchingLines.size()) << " rows corresponding to the filter found. \n";
		}
		if (found)
		{
			matchingLines.push_back(row);
		}
	}
	std::cout << "Filtered to only values lower than or equal to " << inputValue << ".\n";
	std::cout << debugCounter << " rows searched, " << Utils::subtractTitles(matchingLines.size()) << " matches found.\n";
	LogData::logContents.push_back(matchingLines);
}
