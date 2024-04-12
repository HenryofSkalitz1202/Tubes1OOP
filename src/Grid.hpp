#ifndef GRID_HPP
#define GRID_HPP
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Grid{
protected:
  std::vector<std::vector<T*>> data; 
  size_t rows;
  size_t cols;

public:
  Grid(size_t rows, size_t cols);
  ~Grid();
  T*& get(size_t row, size_t col);
  void set(size_t row, size_t col, T& value);
  void set_first_empty(T& value);
  void unset(size_t row, size_t col);
  bool is_empty(size_t row, size_t col);
  size_t numRows() const;
  size_t numCols() const;
  bool is_full();
  bool has_type(T& value);
  //void printLexicalOrder(ostream& st, int n);
  template <class u> friend ostream& operator<<(ostream& st, Grid<u> &grid);
};

#endif