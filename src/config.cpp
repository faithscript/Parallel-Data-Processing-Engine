#include "config.h"
#include <iostream>
#include <sstream>

Config::Config(int argc, char* argv[]) : file_path("test.csv"), file_size_mb(10) {
    thread_counts = {1, 2, 4, 8};
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            file_path = argv[++i];
        } else if (arg == "--threads" && i + 1 < argc) {
            thread_counts.clear();
            std::stringstream ss(argv[++i]);
            int t;
            while (ss >> t) {
                thread_counts.push_back(t);
                if (ss.peek() == ',') ss.ignore();
            }
        } else if (arg == "--size" && i + 1 < argc) {
            file_size_mb = std::stoul(argv[++i]);
        }
    }
} 