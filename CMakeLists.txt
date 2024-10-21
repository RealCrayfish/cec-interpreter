cmake_minimum_required(VERSION 3.30)
project(cecLangInterpreter)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(cecLangInterpreter
    include/cec.hpp
    include/utilities.hpp
        src/main.cpp)
