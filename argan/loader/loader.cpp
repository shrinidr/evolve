#include "loader/build_file.hpp"
#include "loader/loader.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <unordered_map>


const std::string BUILD_JSON = "BUILD.json";

void print_rule_map(const rule_map& m) {
    for (const auto& [key, files] : m) {
        std::cout << key << ": [";
        for (size_t i = 0; i < files.size(); ++i) {
            std::cout << files[i];
            if (i + 1 < files.size()) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

RawTargets Loader::load(const std::string& build_path) {

    std::filesystem::path targetPath = build_path;

    // Package level data.
    rule_map build_dict;

    if (std::filesystem::exists(targetPath) && std::filesystem::is_directory(targetPath)) {
        if (!Loader::buildPackage(targetPath, "", &build_dict)){
            std::cout << "Building packages from root FAILED" << std::endl; 
            return RawTargets{build_path, {}};
        }
        // Check if the global package dictionary makes sense.
        std::cout << "Packages created without any errors!" << std::endl;
        std::cout << "Packages keyed by build paths:" << std::endl; 
        print_rule_map(build_dict);
        auto [ok, raw_targets] = Loader::parser(&build_dict);

    } else {
        std::cerr << "The provided path does not exist or is not a directory." << std::endl;
    }

    return RawTargets{build_path, {}};
}

// Parse all the build files inside the global package 
// mapping, check for correctness and create RawTargets
std::pair<bool, RawTargets> Loader::parser(rule_map* package_dict) {

}



bool path_ends_with(const std::filesystem::path& p, 
                    const std::string& suffix) {
    std::string path_str = p.generic_string();

    if (path_str.length() >= suffix.length()) {
        return path_str.compare(path_str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }
    return false;
}


/** If for the folder at path, there is no build file at the root,
 * assign the global dictionary at build_root key, all the files inside this directory.
 * 
 */

bool Loader::buildPackage(const std::filesystem::path path,
                          std::string build_root,
                          rule_map* buildMap){

    std::vector<std::string> tempFiles = {};
    std::vector<std::filesystem::path> tempFolders = {};
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
                        std::cout << "Multiple BUILD.json files observed in " << path << std::endl;
                        return false;
                    } else {
                        isBuildFile = true;
                        build_root = filestr;
                        // buildMap[filestr] can be non empty.
                        (*buildMap)[filestr] = tempFiles;
                        tempFiles = {};
                    }
                } else {
                    // If already seen the build file in this dir,
                    // add this file to that build files key in the map.
                    if (isBuildFile)
                        (*buildMap)[build_root].push_back(filestr);
                    else 
                        tempFiles.push_back(filestr);
                }
            } else {
                if (isBuildFile){
                    if (!Loader::buildPackage(filepath, build_root, buildMap))
                        return false;
                }  
                else
                    tempFolders.push_back(filepath);
            }
        }
        // Add all files to the build_root either coming from parent/defined in this dir.
        // Call all sub-folders with this build_root.

        for (const auto& entry : tempFiles){
            (*buildMap)[build_root].push_back(entry);
        }
        for (const auto& entry : tempFolders){
            if (!Loader::buildPackage(entry, build_root, buildMap))
                return false;
        }
    } else {
        std::cerr << "The provided path does not exist or is not a directory." << std::endl;
        return false;
    }
    return true;
}



