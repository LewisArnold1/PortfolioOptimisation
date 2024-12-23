# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(PortfolioOptimiser)
set(CMAKE_CXX_STANDARD 17)

# Executable and source files
add_executable(portfolio_optimiser src/main.cpp)

# vcpkg
set(CMAKE_TOOLCHAIN_FILE "/Users/lewisarnold1/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Link external libraries
find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

target_link_libraries(portfolio_optimiser PRIVATE nlohmann_json::nlohmann_json CURL::libcurl)
