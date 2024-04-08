#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class FileReader {
public:
    explicit FileReader(const std::string& filePath) : filePath(filePath) {}

    std::string readText() const {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file: " + filePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf(); // Read the entire file into the stringstream
        file.close(); // Close the file

        return buffer.str(); // Return the content as a string
    }

private:
    std::string filePath;
};
