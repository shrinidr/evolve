#pragma once

#include "model/target.hpp"

class Graph {};

class Analyzer {
public:
    static Graph analyze(const RawTargets& raw_targets);
};
