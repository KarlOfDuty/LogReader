#include "Filesystem.hpp"

#ifdef _WIN32 // Windows only

bool Filesystem::initialize(const std::string& path)
{
	readFilePaths(path);

	if (fileList.empty())
	{
		std::cout << "No logs present in ./logs. Aborting...\n";
		return false;
	}

	std::cout << "Done.\n";
	std::cout << "Reading logs...\n";
	readLogs();
	return true;
}

void Filesystem::readFilePaths(const std::string& path)
{
    std::vector<std::string> files = {};

	try
	{
		//Get the files in alphabetical order aka sorted by time
	    for (auto& file : std::filesystem::directory_iterator(path))
	    {
	        if (std::filesystem::is_regular_file(file))
	        {
	            const size_t dot = file.path().string().find_last_of('.');
	            std::string fileExt = file.path().string().substr(dot, file.path().string().size() - dot);
	            if (fileExt == ".log")
	            {
	                files.push_back(file.path().string());
	                std::cout << " Found " << file.path().string() << "'\n";
	            }
	        }
	    }
	}
	catch (std::filesystem::filesystem_error&) { return; }

	Filesystem::fileList = files;
}

#else // Unix only

void Filesystem::readFilePaths(const std::string& path)
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
	Filesystem::fileList = files;
}

#endif

void Filesystem::readLogs()
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
			logContents.back().emplace_back("");
		}
		while (std::getline(file, logContents.back().back()));
		file.close();
	}
}