#include "general_helpers.hpp"

std::string extractFileName(const std::string path) {
    size_t found = path.find_last_of("/\\"); // Find the last directory separator
    if (found != std::string::npos) {
        return path.substr(found + 1); // Extract the substring after the separator
    }
    return path; // No separator found, return the original path
}

std::string extractDirectoryName(const std::string path) {
    size_t found = path.find_last_of("/\\"); // Find the last directory separator
    if (found != std::string::npos) {
        return path.substr(0, found + 1); // Extract the substring before the separator
    }
    return ""; // No separator found
}