﻿# CMakeList.txt : CMake project for LogReader, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("LogReader")

# Add source to this project's executable.
add_executable (LogReader "main.cpp" "filesystem.cpp" "commands/filter_command.cpp" "logreader.cpp" "commands/save_command.cpp")

# TODO: Add tests and install targets if needed.
