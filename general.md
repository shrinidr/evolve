First part: working DAG exectuor with content addressed caching, rules
defined in json or toml files. Hash declared inputs to produce cache key.
Check local cache dir before executing. Execute actions in parallel using threadpool. 


Resources:
bazel.build/reference/skyframe.
Build systems a la carte.
