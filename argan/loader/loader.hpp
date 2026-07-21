#pragma once

#include <string>

#include "model/target.hpp"

class Loader {
public:
    static RawTargets load(const std::string& build_path);
};
