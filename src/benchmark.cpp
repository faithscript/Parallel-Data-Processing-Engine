#include "benchmark.h"
#include "file_reader.h"
#include "data_processor.h"
#include "thread_pool.h"
#include "performance_monitor.h"
#include <chrono>
#include <iostream>

Benchmark::Benchmark(const std::string& file_path, const std::vector<int>& thread_counts)
    : file_path(file_path), thread_counts(thread_counts) {}

std::vector<Benchmark::Result> Benchmark::run() {
    std::vector<Result> results;
    for (int threads : thread_counts) {
        FileReader reader(file_path);
        DataProcessor processor;
        ThreadPool pool(threads);
        std::atomic<uint64_t> processed_rows{0};
        auto get_count = [&processed_rows]() { return processed_rows.load(); };
        PerformanceMonitor monitor(get_count, 200);
        monitor.start([](double, size_t){}); // No-op callback
        auto start = std::chrono::steady_clock::now();
        std::vector<std::future<void>> futures;
        while (auto chunk = reader.next_chunk()) {
            futures.push_back(pool.enqueue([chunk, &processor, &processed_rows]() {
                processor.process_chunk(*chunk);
                processed_rows += chunk->size();
            }));
        }
        for (auto& f : futures) f.get();
        auto end = std::chrono::steady_clock::now();
        monitor.stop();
        double duration = std::chrono::duration<double>(end - start).count();
        uint64_t sum, count;
        double avg;
        processor.get_results(sum, count, avg);
        size_t mem = monitor.get_memory_usage();
        results.push_back(Result{threads, duration, count/duration, mem});
    }
    return results;
} 