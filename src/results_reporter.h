#pragma once
#include <vector>
#include <string>
#include "benchmark.h"

// ResultsReporter outputs formatted performance comparisons.
class ResultsReporter {
public:
    static void report(const std::vector<Benchmark::Result>& results);
}; 