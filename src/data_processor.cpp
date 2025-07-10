#include "data_processor.h"
#include <sstream>

DataProcessor::DataProcessor() : sum(0), count(0) {}

void DataProcessor::process_chunk(const std::vector<std::string>& lines) {
    uint64_t local_sum = 0;
    uint64_t local_count = 0;
    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::string cell;
        while (std::getline(iss, cell, ',')) {
            try {
                local_sum += std::stoull(cell);
                ++local_count;
            } catch (...) {
                // Ignore non-numeric cells
            }
        }
    }
    std::lock_guard<std::mutex> lock(mtx);
    sum += local_sum;
    count += local_count;
}

void DataProcessor::get_results(uint64_t& out_sum, uint64_t& out_count, double& average) const {
    std::lock_guard<std::mutex> lock(mtx);
    out_sum = sum;
    out_count = count;
    average = (count > 0) ? static_cast<double>(sum) / count : 0.0;
}

void DataProcessor::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    sum = 0;
    count = 0;
} 