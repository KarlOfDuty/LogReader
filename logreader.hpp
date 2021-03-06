#pragma once
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "commands/filter_command.hpp"
#include "commands/save_command.hpp"
#include "commands/command_parser.hpp"
#include "filesystem.hpp"

class LogReader
{
public:
	const std::string VERSION = "0.1.2";
	const std::string HELP_MESSAGE =
	{
		"LogReader " + VERSION + "                                 .oO List of commands Oo.\n" +
		"--------------------------------------------------------------------------------------------------------------------\n" +
		"* quit:                              Quit Log Reader\n" +
		"* print:                             Prints all log contents.\n" +
		"* save:                              Saves all log contents to output.log.\n" +
		"* filter phrase <phrase>:            Filters out lines from the logs that do not contain the phrase.\n" +
		"* filter value larger <number>:      Filters out lines from the logs that do not contain a number larger or equal to the one entered.\n" +
		"* filter value smaller <number>:     Filters out lines from the logs that do not contain a number smaller or equal than the one entered.\n" +
		"* undo:                              Undoes the latest action.\n" +
		"* help:                              Prints this help screen\n"
	};

	LogReader();
private:
	FilterCommand filterCommand = {};
	SaveCommand saveCommand = {};

	static void undo();
};
