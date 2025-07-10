cmake_minimum_required(VERSION 3.10)
project(MultiThreadedDataPipeline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MultiThreadedDataPipeline
    src/main.cpp
    src/thread_pool.cpp
    src/file_reader.cpp
    src/data_processor.cpp
    src/performance_monitor.cpp
    src/benchmark.cpp
    src/results_reporter.cpp
    src/config.cpp
    src/data_generator.cpp
)

# For macOS memory usage
if(APPLE)
    target_link_libraries(MultiThreadedDataPipeline PRIVATE "-framework CoreServices")
endif() 