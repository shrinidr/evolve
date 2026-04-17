Some linux commands that will be reused frequently:

**To run a cpp file using clang.**
clang++ -O3 main.cpp -o main
    O3 enables a lot of optimizations 


**To see the LLVM human readable file.**
clang++ -S -emit-llvm hello.cpp -o hello.ll
