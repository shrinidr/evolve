#include "loader/build_file.hpp"
#include "loader/loader.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <unordered_map>


const std::string BUILD_JSON = "BUILD.json";

RawTargets Loader::load(const std::string& build_path) {

    std::filesystem::path targetPath = build_path;

    if (std::filesystem::exists(targetPath) && std::filesystem::is_directory(targetPath)) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(targetPath)) {
            std::cout << entry.path().string() << std::endl;
        }
    } else {
        std::cerr << "The provided path does not exist or is not a directory." << std::endl;
    }

    return RawTargets{build_path, {}};
}

bool path_ends_with(const std::filesystem::path& p, const std::string& suffix) {
    std::string path_str = p.generic_string();

    if (path_str.length() >= suffix.length()) {
        return path_str.compare(path_str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }
    return false;
}


/** If for the folder at path, there is no build file at the root,
 * assign the global dictionary at build_root key, all the files inside this directory.
 * 
 * Change the dictionary to be a global entity passed in by the parent function
 * call.
 */

auto Loader::buildPackage(const std::filesystem::path path, std::string build_root){

    std::unordered_map<std::string, std::vector<std::string>> buildMap;
    std::vector<std::string> tempFiles = {};
    std::vector<std::string> tempFolders = {};
    bool isBuildFile = false;

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::error_code ec;
            std::filesystem::path filepath = entry.path(); 
            const std::string filestr = filepath.string();

            if (std::filesystem::is_regular_file(filepath, ec)){
                if (path_ends_with(filepath, BUILD_JSON)){
                    if (isBuildFile){
                        // break bc we cant have 2 build files in the same folder.
                    } else {
                        isBuildFile = true;
                        build_root = filestr;
                        buildMap[filestr] = tempFiles;
                        tempFiles = {};
                    }
                } else {
                    // If already seen the build file in this dir,
                    // add this file to that build files key in the map.
                    if (isBuildFile)
                        buildMap[build_root].push_back(filestr);
                    else 
                        tempFiles.push_back(filestr);
                }
            } else {
                if (isBuildFile)
                    Loader::buildPackage(filepath, build_root);
                else
                    tempFolders.push_back(filestr);
            }
        }

        if (!isBuildFile){
            for (const auto& entry : tempFiles){

            }

        }
    }
    else {
        std::cerr << "The provided path does not exist or is not a directory." << std::endl;
        return;
        }
    }



