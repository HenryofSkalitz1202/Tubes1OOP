#include "Grid.hpp"
#include <iostream>
#include <iomanip>

template <typename T>
Grid<T>::Grid(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<T>(cols));
}

template <typename T>
T Grid<T>::get(size_t row, size_t col) const {
    return data[row][col];
}

template <typename T>
void Grid<T>::set(size_t row, size_t col, const T& value) {
    data[row][col] = value;
}

template <typename T>
size_t Grid<T>::numRows() const {
    return rows;
}

template <typename T>
size_t Grid<T>::numCols() const {
    return cols;
}

template <typename T>
void Grid<T>::printLexicalOrder(int n) {
    char current = 'A'; // Start from 'A' (uppercase)
    int count = 0;

    while (count < n) {
        for(int i = 0; i < 5; i++){
            std::cout << " ";
        }
        
        std::cout << current;
        count++;
        current++;

        // If current character reaches 'Z', reset it to 'A'
        if (current > 'Z') {
            current = 'A';
        }
    }
    std::cout << std::endl;
}

void printBorder(int n) {
    std::cout << "   ";
    for(int i = 0; i < n; i++) {
        std::cout << "+-----";
    }
    std::cout << "+" << std::endl;
}

template <typename T>
void Grid<T>::print() const {
    std::cout << " ";
    printLexicalOrder(this->cols);
    for (size_t i = 0; i < rows; ++i){
        printBorder(this->cols);
        std::cout << std::setw(2) << std::setfill('0') << i+1;

        std::cout << " | " ;
        for (size_t j = 0; j < cols; ++j) {
            std::cout << std::setw(3) << std::setfill('0') << data[i][j] << " | ";
        }
        std::cout << "  " << endl;
    }
    printBorder(this->cols);
}

int main() {
    // Create a 3x3 grid of integers
    Grid<int> grid(6, 6);

    // Set values in the grid
    for (size_t i = 0; i < grid.numRows(); ++i) {
        for (size_t j = 0; j < grid.numCols(); ++j) {
            grid.set(i, j, i + j);
        }
    }

    // Print the grid
    grid.print();

    // Test the get method
    std::cout << "Value at position (1, 2): " << grid.get(1, 2) << std::endl;

    return 0;
}

