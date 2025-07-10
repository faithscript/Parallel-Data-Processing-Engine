#include "performance_monitor.h"
#include <iostream>
#ifdef __APPLE__
#include <mach/mach.h>
#endif

PerformanceMonitor::PerformanceMonitor(const std::function<uint64_t()>& get_count_fn, int interval_ms)
    : running(false), get_count(get_count_fn), interval_ms(interval_ms) {}

PerformanceMonitor::~PerformanceMonitor() {
    stop();
}

void PerformanceMonitor::start(const StatsCallback& cb) {
    if (running) return;
    running = true;
    monitor_thread = std::thread([this, cb] { monitor_loop(cb); });
}

void PerformanceMonitor::stop() {
    running = false;
    if (monitor_thread.joinable()) monitor_thread.join();
}

void PerformanceMonitor::monitor_loop(const StatsCallback& cb) {
    uint64_t last_count = get_count();
    auto last_time = std::chrono::steady_clock::now();
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        uint64_t curr_count = get_count();
        auto curr_time = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(curr_time - last_time).count();
        double rows_per_sec = (curr_count - last_count) / elapsed;
        size_t mem = get_memory_usage();
        cb(rows_per_sec, mem);
        last_count = curr_count;
        last_time = curr_time;
    }
}

size_t PerformanceMonitor::get_memory_usage() const {
#ifdef __APPLE__
    struct mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &infoCount) != KERN_SUCCESS)
        return 0;
    return info.resident_size;
#else
    return 0; // Not implemented for other platforms
#endif
} 