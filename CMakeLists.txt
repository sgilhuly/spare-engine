# Define the project
cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
project (SpareEngine VERSION 0.1 LANGUAGES C CXX)

# Some settings
set (CMAKE_CXX_STANDARD 11)

# Project dependencies
find_package (AssImp REQUIRED)

add_subdirectory (src)
target_link_libraries (SpareEngine ${AssImp_LIBS})
