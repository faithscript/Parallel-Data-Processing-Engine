#include "file_reader.h"
#include <sstream>

FileReader::FileReader(const std::string& filename, size_t chunk_size)
    : file(filename), chunk_size(chunk_size), end_of_file(false) {
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

FileReader::~FileReader() {
    if (file.is_open()) file.close();
}

std::optional<std::vector<std::string>> FileReader::next_chunk() {
    std::lock_guard<std::mutex> lock(mtx);
    if (end_of_file) return std::nullopt;
    std::vector<std::string> chunk;
    std::string line;
    for (size_t i = 0; i < chunk_size && std::getline(file, line); ++i) {
        chunk.push_back(line);
    }
    if (chunk.empty()) {
        end_of_file = true;
        return std::nullopt;
    }
    if (file.eof()) end_of_file = true;
    return chunk;
}

bool FileReader::eof() const {
    std::lock_guard<std::mutex> lock(mtx);
    return end_of_file;
} 