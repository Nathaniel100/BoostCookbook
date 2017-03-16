cmake_minimum_required(VERSION 3.6)
project(BoostCookbook)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
