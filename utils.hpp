#pragma once

#include <cstring>
#include "filesystem.hpp"

class Utils
{
public:
	static bool isNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
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

