#include "data_generator.h"
#include <fstream>
#include <random>
#include <string>

void DataGenerator::generate(const std::string& filename, size_t size_mb) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Failed to create file: " + filename);
    std::mt19937 rng(42);
    std::uniform_int_distribution<uint64_t> dist(1, 1000000);
    size_t bytes_written = 0;
    const size_t target_bytes = size_mb * 1024 * 1024;
    const int cols = 10;
    std::string line;
    while (bytes_written < target_bytes) {
        line.clear();
        for (int i = 0; i < cols; ++i) {
            line += std::to_string(dist(rng));
            if (i < cols - 1) line += ", ";
        }
        line += "\n";
        file << line;
        bytes_written += line.size();
    }
    file.close();
} 