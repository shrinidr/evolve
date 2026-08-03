#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>
#include "model/target.hpp"

using rule_map = std::unordered_map<std::string, std::vector<std::string>>;

class Loader {
public:
    static RawTargets load(const std::string& build_path);

    static bool buildPackage(const std::filesystem::path path,
                      std::string build_root,
                      rule_map* buildMap);

    static std::pair<bool, RawTargets> parser(rule_map* package_dict);
};
