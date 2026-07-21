#pragma once

#include <string>
#include <vector>

struct Target {
    std::string package;
    std::string name;
    std::string type;
    std::vector<std::string> srcs;
    std::vector<std::string> hdrs;
    std::vector<std::string> deps;
    std::vector<std::string> data;
};

struct RawTargets {
    std::string build_path;
    std::vector<Target> targets;
};
