#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace eiririn {
    static std::string stringFromFile(string p_path) {
        std::ifstream ifs(p_path);
        return string((std::istreambuf_iterator<char>(ifs)),
                            (istreambuf_iterator<char>()));
    };    // Returns the contents of a file as a string
}