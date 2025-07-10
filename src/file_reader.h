#pragma once
#include <string>
#include <fstream>
#include <mutex> // thread synchronization
#include <vector>
#include <optional>

// FileReader reads a CSV file in chunks (by lines) and provides thread-safe access.
class FileReader {
public:
    FileReader(const std::string& filename, size_t chunk_size = 1000);
    ~FileReader();

    // Returns the next chunk of lines, or std::nullopt if EOF.
    std::optional<std::vector<std::string>> next_chunk();
    bool eof() const;

private:
    std::ifstream file;
    size_t chunk_size;
    mutable std::mutex mtx;
    bool end_of_file;
}; 