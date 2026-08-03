#include "loader/build_file.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string read_build_file(const std::string& build_path) {
    std::ifstream file(build_path);
    if (!file) {
        throw std::runtime_error("Could not open build file: " + build_path);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

RawTargets parse_build_file(const std::string& build_path, const std::string& contents) {
    nlohmann::json build_obj = nlohmann::json::parse(contents);

    RawTargets raw_targets{build_path, {}};

    // Loop over all the targets inside of a build file.

    for (const auto& t : build_obj.at("targets")) {
        Target target;
        target.package = build_path;
        target.name = t.at("name").get<std::string>();
        target.type = t.at("type").get<std::string>();
        target.srcs = t.value("srcs", std::vector<std::string>{});
        target.hdrs = t.value("hdrs", std::vector<std::string>{});
        target.deps = t.value("deps", std::vector<std::string>{});
        target.data = t.value("data", std::vector<std::string>{});
        raw_targets.targets.push_back(std::move(target));
    }

    return raw_targets;
}
