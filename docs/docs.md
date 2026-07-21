Dev Phase #1 Rules 

Load -> Analyze -> Execute.

1) Every dependency is specified in a BUILD.json file at a given directories'
root. 
2) Currently, only support equivalents of Bazel's cc_binary, library and cc_test.
3) [07/12] Building out the rule system for build files and the parser code.
4) Need to support cross directory dependencies.



Rules:

1) cppbin:
    a) Start off with standard arguments: srcs, data, hdrs, deps and name.
       For srcs, for now, lets just have .cpp files. We can eventually combine hdrs into
       srcs and also add support to reference cross folder targets as parts of srcs.

    b) name should be the same as the name of source file that is entrypoint to this binary.
    c) Need to decide on what attrs are mandatory and what are not. (Name and srcs probably is
    mandatory.)


2) cpplib


