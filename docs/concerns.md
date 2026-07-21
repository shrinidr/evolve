We currently have recursive directory traversal from a given root.
But we need some plan to make sure that there is an appropriate number
of build files at every depth of the folder. 

1) For a given folder at the root level, there can only be a single build file.
2) Every nested sub folder can have atmost one file and no build file having folders are allowed.
3) For all sub-dirs inside of a dir, if any sub-dir does not have a Build file of its own, its contents are owned by the parent dir at the root which does have a build file. This is the concept of disjoint packages inside Bazel.
4) I will create a dictionary mapping build file paths to the an array of all files present in the package that this build file represents, validate if user specified dependencies follow the package level constraints and then create the whatever rawtargets array.  



