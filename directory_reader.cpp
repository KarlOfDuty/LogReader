#include "directory_reader.hpp"

#ifdef _WIN32 // Windows only

std::vector<std::string> DirectoryReader::getFilePaths(const std::string path)
{
    std::vector<std::string> fileList = {};

    //Get the files in alphabetical order aka sorted by time
    for (auto& file : std::filesystem::directory_iterator(path))
    {
        if (std::filesystem::is_regular_file(file))
        {
            const size_t dot = file.path().string().find_last_of('.');
            std::string fileExt = file.path().string().substr(dot, file.path().string().size() - dot);
            if (fileExt == ".log")
            {
                fileList.push_back(file.path().string());
                std::cout << " Found " << file.path().string() << "'\n";
            }
        }
    }
    return fileList;
}

#else // Unix only

std::vector<std::string> DirectoryReader::getFilePaths(const std::string path) 
{
    DIR* directory = opendir(path.c_str());

    if (directory == nullptr)
    {
        return std::vector<std::string>();
    }

    std::vector<std::string> files;
    struct dirent* ent;
    while ((ent = readdir(directory)) != nullptr)
    {
        if (ent->d_type == DT_REG) // regular file
        {
            files.push_back(path + ent->d_name);
            std::cout << " Found '" << ent->d_name << "'\n";
        }
    }

    closedir(directory);
    return files;
}

#endif