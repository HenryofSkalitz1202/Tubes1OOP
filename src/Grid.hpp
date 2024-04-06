#ifndef GRID_HPP
#define GRID_HPP
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Grid{
protected:
  std::vector<std::vector<T>> data; 
  size_t rows;
  size_t cols;

public:
  Grid(size_t rows, size_t cols);
  T get(size_t row, size_t col) const;
  void set(size_t row, size_t col, const T& value);
  size_t numRows() const;
  size_t numCols() const;
  static void printLexicalOrder(int n);
  void print() const;
};

// template<>
// class Ladang : public Grid<Tumbuhan>{
// public:
//   void printLadang();
// };

// template<>
// class Peternakan : public Grid<Hewan>{
// public:
//   void printPeternakan();
// };

#endif