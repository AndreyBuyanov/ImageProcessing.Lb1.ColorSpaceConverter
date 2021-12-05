cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(SetupGlobalConfig)

project(CSC)

include(InstallDeps)

add_subdirectory(CSCEngine)
add_subdirectory(CSCViewer)
