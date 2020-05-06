#pragma once

#include <vector>
#include <string>
#include <iostream>

#ifdef _WIN32 // Windows only
    #include <filesystem>
#else // Unix only
    #include <dirent.h>
#endif

class DirectoryReader {
public:
    static std::vector<std::string> getFilePaths(const std::string& path);
};

