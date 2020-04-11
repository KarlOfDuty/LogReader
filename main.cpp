#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <string.h>
#include "directory_reader.hpp"

void printAll();
void saveAll();
void undo();
bool getLogs();
bool readLogs();
bool isProtectedLine(const std::string& line);
size_t subtractTitles(const size_t rowsWithTitles, const size_t numberOfTitles);
std::string parseCommandString(const std::string &input, std::vector<std::string> &parameters);
std::string help();

std::vector<std::string> fileList = {};
std::vector<std::vector<std::string>> logContents = {};
std::string version = "0.1.0";
int main()
{
    std::cout << "Fetching logs...\n";
    if (getLogs())
    {
        std::cout << "Done.\n";
        std::cout << "Reading logs...\n";
        if (readLogs())
        {
            std::cout << "Done. " << logContents.back().size() << " rows.\n";
            while (true)
            {
                std::string input = "";

                std::cout << "> ";
                std::getline(std::cin, input);

                std::vector<std::string> parameters = {};
                std::string command = parseCommandString(input, parameters);
                if (command == "printAll" || command == "printall")
                {
                    std::cout << "Printing logs...\n";
                    printAll();
                }
                else if (command == "saveAll" || command == "saveall")
                {
                    saveAll();
                }
                else if (command == "undo")
                {
                    undo();
                }
                else if (command == "filter")
                {
                    if (!parameters.empty())
                    {
                        std::vector<std::string> matchingLines = {};
                        matchingLines.reserve(logContents.back().size());

                        std::string filterCommand = parameters.front();
                        parameters.erase(parameters.begin());

                        if (filterCommand == "phrase")
                        {
                            std::string phrase = "";
                            while (!parameters.empty())
                            {
                                phrase.append(parameters.front());
                                parameters.erase(parameters.begin());
                                phrase.append(" ");
                            }
                            phrase.erase(phrase.end() - 1);
                            std::cout << "Filtering to lines containing the phrase: '" << phrase << "'\n";
                            if (!phrase.empty())
                            {
                                int debugCounter = 0;
                                for (std::string& row : logContents.back())
                                {
                                    if (row.find(phrase) != std::string::npos || isProtectedLine(row))
                                    {
                                        matchingLines.push_back(row);
                                    }
                                    debugCounter++;
                                    if (!(debugCounter % 10000))
                                    {
                                        std::cout << "Processed " << debugCounter << " rows. " << subtractTitles(matchingLines.size(), fileList.size()) << " rows corresponding to the filter found.\n";
                                    }
                                }
                                std::cout << "Done. " << debugCounter << " rows searched, " << subtractTitles(matchingLines.size(), fileList.size()) << " matches found.\n";
                                logContents.push_back(matchingLines);
                            }
                            else
                            {
                                std::cout << "No phrase supplied.\n";
                            }
                        }
                        else if (filterCommand == "value")
                        {
                            std::string functionCommand = parameters.front();
                            parameters.erase(parameters.begin());
                            if (functionCommand == "lessThan")
                            {
                                float inputValue = std::strtof(parameters.front().c_str(), nullptr);
                                parameters.erase(parameters.begin());

                                int debugCounter = 0;
                                for (std::string& row : logContents.back())
                                {
                                    std::stringstream ss = std::stringstream();
                                    std::string word = "";
                                    ss << row;
                                    bool found = isProtectedLine(row);
                                    while (ss && !found)
                                    {
                                        ss >> word;
                                        if (std::strtof(word.c_str(), nullptr) <= inputValue)
                                        {
                                            found = true;
                                        }
                                    }
                                    debugCounter++;
                                    if (!(debugCounter % 10000))
                                    {
                                        std::cout << "Processed " << debugCounter << " rows. " << subtractTitles(matchingLines.size(), fileList.size()) << " rows corresponding to the filter found. \n";
                                    }
                                    if (found)
                                    {
                                        matchingLines.push_back(row);
                                    }
                                }
                                std::cout << "Filtered to only values lower than or equal to " << inputValue << ".\n";
                                logContents.push_back(matchingLines);
                            }
                            if (functionCommand == "moreThan")
                            {
                                float inputValue = std::strtof(parameters.front().c_str(), nullptr);
                                parameters.erase(parameters.begin());

                                int debugCounter = 0;
                                for (std::string& row : logContents.back())
                                {
                                    std::stringstream ss = std::stringstream();
                                    std::string word = "";
                                    ss << row;
                                    bool found = isProtectedLine(row);
                                    while (ss && !found)
                                    {
                                        ss >> word;
                                        if (std::strtof(word.c_str(), nullptr) >= inputValue)
                                        {
                                            found = true;
                                        }
                                    }
                                    debugCounter++;
                                    if (!(debugCounter % 10000))
                                    {
                                        std::cout << "Processed " << debugCounter << " rows. " << subtractTitles(matchingLines.size(), fileList.size()) << " rows corresponding to the filter found. \n";
                                    }
                                    if (found)
                                    {
                                        matchingLines.push_back(row);
                                    }
                                }
                                std::cout << "Filtered to only values higher than or equal to " << inputValue << ".\n";
                                logContents.push_back(matchingLines);
                            }
                        }
                        else
                        {
                            std::cout << "Invalid subcommand. Use 'help' for a full list of commands.\n";
                        }
                    }
                }
                else if (command == "help")
                {
                    std::cout << help();
                }
                else if (command == "quit" || command == "exit" || command == "stop")
                {
                    break;
                }
                else
                {
                    std::cout << "Invalid command. Use 'help' for a full list of commands.\n";
                }
            }
        }
        else
        {
            std::cout << "Error reading from log files, check read access and that logs still exist. Aborting...\n";
        }
    }
    else
    {
        std::cout << "No logs present in ./logs. Aborting...\n";
    }
    return 0;
}
bool getLogs()
{
    fileList = DirectoryReader::getFilePaths("logs/");

    return !fileList.empty();
}
bool readLogs()
{
    std::fstream file = std::fstream();
    logContents.emplace_back(std::vector<std::string>());
    for (std::string& fileName : fileList)
    {
        std::cout << " Reading " << fileName << "...\n";
        logContents.back().emplace_back("-- File: " + fileName + " --");
        file.open(fileName);
        do
        {
            logContents.back().emplace_back("HELLO");
        }
        while (std::getline(file, logContents.back().back()));
        file.close();
    }
    return true;
}
// Checks if a line is protected from removal, right now only file separators are protected
bool isProtectedLine(const std::string &line)
{
    return !strncmp(line.c_str(), "-- File: ", 9);
}

size_t subtractTitles(const size_t rowsWithTitles, const size_t numberOfTitles)
{
    return rowsWithTitles > numberOfTitles ? rowsWithTitles - numberOfTitles : 0;
}

// Returns the base command and enters all parameters into the supplied vector
std::string parseCommandString(const std::string &input, std::vector<std::string> &parameters)
{
    std::stringstream ss(input);

    std::string baseCommand = "";
    ss >> baseCommand;

    std::string parameter;
    while (ss.good())
    {
        ss >> parameter;
        parameters.push_back(parameter);
    }
    return baseCommand;
}

void undo()
{
    if (logContents.size() > 1)
    {
        logContents.pop_back();
        std::cout << "Last action undone.\n";
    }
    else
    {
        std::cout << "No actions left to undo.\n";
    }
}

void printAll()
{
    for (std::string& row : logContents.back())
    {
        std::cout << "'" << row << "'\n";
    }
}

void saveAll()
{
    std::cout << "Saving log file...\n";
    std::string outString;
    for (std::string& row : logContents.back())
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

std::string help()
{
    std::string helpStr;
    helpStr += "LogReader "; helpStr += version;
    helpStr += "                                 .oO List of commands Oo.\n";
    helpStr += "--------------------------------------------------------------------------------------------------------------------\n";
    helpStr += "* quit:                                         Quit Log Reader\n";
    helpStr += "* printAll:                                     Prints all log contents.\n";
    helpStr += "* filter phrase <phrase>:                       Filters out lines from the logs that do not contain the phrase.\n";
    helpStr += "* filter value moreThan <number>:               Filters out lines from the logs that do not contain a number higher or equal to the one entered.\n";
    helpStr += "* filter value lessThan <number>:               Filters out lines from the logs that do not contain a number lower or equal than the one entered.\n";
    helpStr += "* undo:                                         Undoes the latest action.\n";
    helpStr += "* help:                                         Prints this help screen\n";
    return helpStr;
}