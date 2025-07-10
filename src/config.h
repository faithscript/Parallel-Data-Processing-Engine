#pragma once
#include <string>
#include <vector>

// Config holds settings for the pipeline.
class Config {
public:
    Config(int argc, char* argv[]);
    std::string file_path;
    std::vector<int> thread_counts;
    size_t file_size_mb;
}; 