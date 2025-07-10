#pragma once
#include <string>

// DataGenerator creates test CSV files of a given size (in MB).
class DataGenerator {
public:
    static void generate(const std::string& filename, size_t size_mb);
}; 