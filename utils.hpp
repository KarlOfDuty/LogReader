#pragma once

static std::vector<std::string> fileList;
static std::vector<std::vector<std::string>> logContents;

static bool isProtectedLine(const std::string& line)
{
	return !strncmp(line.c_str(), "-- File: ", 9);
}

static size_t subtractTitles(const size_t rowsWithTitles)
{
	return rowsWithTitles > fileList.size() ? rowsWithTitles - fileList.size() : 0;
}

template <class T>
static T extractFrontOrDefault(std::vector<T>& objects)
{
	if (objects.empty()) return T();

	T output = objects.front();
	objects.erase(objects.begin());
	return output;
}
