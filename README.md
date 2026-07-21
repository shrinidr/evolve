This is the design document for the argan build system.
It is touted to very closely mimic bazel with explicit depedency
declrations via json files (a more sophisticated language can be developed later)


1) Formalize build language schema, we need atleast cc_binary, cc_library and test. Start with this by reading how it is implemented by bazel/

2) Write a parser to parse build files.
