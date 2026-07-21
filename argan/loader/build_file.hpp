#pragma once

#include <string>

#include "model/target.hpp"

// Reads the raw contents of a BUILD.json file from disk.
std::string read_build_file(const std::string& build_path);

// Parses BUILD.json text into a RawTargets value.
RawTargets parse_build_file(const std::string& build_path, const std::string& contents);
