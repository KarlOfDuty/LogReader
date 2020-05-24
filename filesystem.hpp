#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

#ifdef _WIN32 // Windows only
	#include <filesystem>
	#include <windows.h>
	#include <direct.h>
#else // Unix only
	#include <dirent.h>
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

class Filesystem {
public:
	inline static std::vector<std::string> fileList{};
	inline static std::vector<std::vector<std::string>> logContents{};

	static bool initialize();
private:
	static void createDir(const std::string& path);
	static bool dirExists(const std::string& path);
	static void readFilePaths(const std::string& path);
	static void readLogs();
};