#include <iostream>
#include <string>
#include "analyzer/analyzer.hpp"
#include "executor/executor.hpp"
#include "loader/loader.hpp"

std::string parse_args(int argc, char** argv);

/**
 * CMD Line call argan run <root_folder> to build from a 
 * given root.
 */
int main(int argc, char** argv) {
    auto build_path = parse_args(argc, argv);
    std::cout << "build_path: " << build_path << std::endl;
    auto raw_targets = Loader::load(build_path);
    auto graph = Analyzer::analyze(raw_targets);
    Executor::execute(graph);
}

std::string parse_args(int argc, char** argv) {
    if (argc != 3 || std::string(argv[1]) != "run") {
        std::cerr << "usage: argan run <build_path>\n";
        std::exit(1);
    }

    return argv[2];
}
