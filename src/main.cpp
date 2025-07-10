#include "config.h"
#include "data_generator.h"
#include "benchmark.h"
#include "results_reporter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Config config(argc, argv);
        std::cout << "[INFO] Generating test CSV file: " << config.file_path << " (" << config.file_size_mb << " MB)...\n";
        DataGenerator::generate(config.file_path, config.file_size_mb);
        std::cout << "[INFO] File generated. Starting benchmarks...\n";
        Benchmark bench(config.file_path, config.thread_counts);
        auto results = bench.run();
        ResultsReporter::report(results);
        std::cout << "[INFO] Done.\n";
    } catch (const std::exception& ex) {
        std::cerr << "[ERROR] " << ex.what() << std::endl;
        return 1;
    }
    return 0;
} 