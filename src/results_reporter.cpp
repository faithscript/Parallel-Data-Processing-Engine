#include "results_reporter.h"
#include <iostream>
#include <iomanip>

void ResultsReporter::report(const std::vector<Benchmark::Result>& results) {
    std::cout << std::left << std::setw(12) << "Threads"
              << std::setw(16) << "Duration(s)"
              << std::setw(18) << "Rows/sec"
              << std::setw(18) << "Memory(bytes)" << std::endl;
    std::cout << std::string(64, '-') << std::endl;
    for (const auto& r : results) {
        std::cout << std::setw(12) << r.thread_count
                  << std::setw(16) << std::fixed << std::setprecision(4) << r.duration_sec
                  << std::setw(18) << std::fixed << std::setprecision(2) << r.rows_per_sec
                  << std::setw(18) << r.memory_bytes << std::endl;
    }
} 