# Parallel-Data-Processing-Engine

This was something I thought through a few months ago and finally implemented, focusing on clean design, efficiency, and extensibility. I will be adding finance data structures and modifications, as this is intended to cater towards finance.
My laptop could recently handle 2048 threads with no issues, and the csv generator can create files of up to 100GB as well. I'm yet to find a limit to these numbers, but after a certain threshold there will probably be diminishing returns performance-wise.

## Features
- **ThreadPool**: Efficiently manages worker threads for parallel processing
- **FileReader**: Reads large CSV files in chunks, thread-safe
- **DataProcessor**: Computes sum, average, and count from CSV data
- **PerformanceMonitor**: Tracks processing speed and memory usage
- **Benchmark**: Tests performance with 1, 2, 4, and 8 threads
- **ResultsReporter**: Outputs formatted performance comparisons
- **Config**: Simple configuration system for thread count and file paths
- **DataGenerator**: Utility to create test CSV files (1MB, 10MB, 100MB, or custom)

## Build Instructions

1. **Clone the repository:**
   ```sh
   git clone https://github.com/faithscript/high-performance-data-pipeline.git
   cd high-performance-data-pipeline
   ```

2. **Build with CMake:**
   ```sh
   cmake -B build
   cmake --build build
   ```
   This will create the executable at `build/MultiThreadedDataPipeline`.

## Usage

Run with default settings (10MB file, 1/2/4/8 threads):
```sh
./build/MultiThreadedDataPipeline
```

Custom options:
- Change file size: `--size 100` (for 100MB file)
- Change file name: `--file mydata.csv`
- Change thread counts: `--threads 1,2,4,8`

Example:
```sh
./build/MultiThreadedDataPipeline --file test100.csv --size 100 --threads 2,4,8
```

## Output
The program generates a test CSV file, runs benchmarks for each thread count, and prints a formatted table comparing performance (duration, rows/sec, memory usage).

---

Feel free to explore, use, or extend this project! 
