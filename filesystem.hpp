#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifdef _WIN32 // Windows only
    #include <filesystem>
#else // Unix only
    #include <dirent.h>
#endif

class Filesystem {
public:
	inline static std::vector<std::string> fileList{};
	inline static std::vector<std::vector<std::string>> logContents{};

	static bool initialize(const std::string& path);
private:
    static void readFilePaths(const std::string& path);
	static void readLogs();
};

