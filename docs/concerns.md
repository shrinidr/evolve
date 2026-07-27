We currently have recursive directory traversal from a given root.
But we need some plan to make sure that there is an appropriate number
of build files at every depth of the folder. 

1) For a given folder at the root level, there can only be a single build file.
2) Every nested sub folder can have atmost one build file and a  folder not having a build file is allowed. 
3) For all sub-dirs inside of a dir, if any sub-dir does not have a Build file of its own, its contents are owned by the parent dir at the root which does have a build file. This is the concept of disjoint packages inside Bazel.
4) I will create a dictionary mapping build file paths to the array of all files present in the package that this build file represents, validate if user specified dependencies follow the package level constraints and then create the whatever rawtargets array.  
5) Also probably need to identify every build filepath with a hash or something. 
6) Cross package dependency refs can only happen through target labels.

Ref: https://bazel.build/versions/6.6.0/concepts/build-ref#:~:text=A%20package%20is%20a%20collection%20of%20related,be%20a%20part%20of%20two%20different%20packages.





