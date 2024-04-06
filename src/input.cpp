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

int main() {
    std::string filePath = "input.txt"; // Replace "input.txt" with your file path
    FileReader fileReader(filePath);
    try {
        std::string fileContent = fileReader.readText();
        std::cout << fileContent << std::endl; // Print the file content
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; // Print any error message
        return 1;
    }

    return 0;
}

