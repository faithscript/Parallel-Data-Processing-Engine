#pragma once
#include <atomic>
#include <thread>
#include <chrono>
#include <string>
#include <functional>

// PerformanceMonitor tracks processing speed and memory usage in a background thread.
class PerformanceMonitor {
public:
    using StatsCallback = std::function<void(double rows_per_sec, size_t memory_bytes)>;
    PerformanceMonitor(const std::function<uint64_t()>& get_count_fn, int interval_ms = 1000);
    ~PerformanceMonitor();
    void start(const StatsCallback& cb);
    void stop();
    size_t get_memory_usage() const;
private:
    std::atomic<bool> running;
    std::thread monitor_thread;
    std::function<uint64_t()> get_count;
    int interval_ms;
    void monitor_loop(const StatsCallback& cb);
}; 