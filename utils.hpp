#pragma once

#include <cstring>
#include "filesystem.hpp"

class Utils
{
public:
	static bool isNumber(const std::string& str)
	{
		std::string::const_iterator it = str.begin();
		while (it != str.end() && std::isdigit(*it)) ++it;
		return !str.empty() && it == str.end();
	}

	static bool isEmptyOrWhitespace(const std::string& str)
	{
		return str.find_first_not_of(' ') == std::string::npos;
	}

	static bool isProtectedLine(const std::string& line)
	{
		return !strncmp(line.c_str(), "-- File: ", 9);
	}

	static size_t subtractTitles(const size_t rowsWithTitles)
	{
		return rowsWithTitles > Filesystem::fileList.size() ? rowsWithTitles - Filesystem::fileList.size() : 0;
	}

	template <class T>
	static T extractFrontOrDefault(std::vector<T>& objects)
	{
		if (objects.empty()) return T();

		T output = objects.front();
		objects.erase(objects.begin());
		return output;
	}
};

