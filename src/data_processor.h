#pragma once
#include <mutex>
#include <cstdint>
#include <string>
#include <vector>

// DataProcessor aggregates statistics from CSV data: sum, average, count.
class DataProcessor {
public:
    DataProcessor();
    void process_chunk(const std::vector<std::string>& lines);
    void get_results(uint64_t& sum, uint64_t& count, double& average) const;
    void reset();
private:
    mutable std::mutex mtx;
    uint64_t sum;
    uint64_t count;
}; 