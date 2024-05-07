#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace cray {
    static std::string stringFromFile(std::string p_path) {
        std::ifstream ifs(p_path);
        return std::string((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));
    };    // Returns the contents of a file as a string
}