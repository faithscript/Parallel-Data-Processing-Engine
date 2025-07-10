#pragma once
#include <vector>
#include <string>
#include <tuple>

// Benchmark runs the pipeline with various thread counts and collects results.
class Benchmark {
public:
    struct Result {
        int thread_count;
        double duration_sec;
        double rows_per_sec;
        size_t memory_bytes;
    };
    Benchmark(const std::string& file_path, const std::vector<int>& thread_counts);
    std::vector<Result> run();
private:
    std::string file_path;
    std::vector<int> thread_counts;
}; 