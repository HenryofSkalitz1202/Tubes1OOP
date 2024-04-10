#ifndef GRID_HPP
#define GRID_HPP
#include "Asset.cpp"
#include "Produk.cpp"
#include "Tumbuhan.cpp"
#include "Hewan.cpp"
#include "Bangunan.cpp"
#include <string>
#include <vector>
#include <map>

using namespace std;

template <typename T>
class Grid{
protected:
  map<string, T> data; 
  size_t rows;
  size_t cols;

public:
  Grid(size_t rows, size_t cols);
  string calculateKey(size_t row, size_t col);
  void set(size_t row, size_t col, T value);
  T get(size_t row, size_t col);
  size_t numRows();
  size_t numCols();
  void printLexicalOrder(int n);
  void printBorder(int n);
  virtual void print() = 0;
};

class Inventory : public Grid<Asset*>{
public:
  // Constructors
  Inventory(size_t rows, size_t cols);
  Inventory(Inventory& other);
  ~Inventory();

  void print();
};

class Ladang : public Grid<Tumbuhan*>{
public:
  Ladang(size_t rows, size_t cols);
  Ladang(Ladang& other);
  ~Ladang();
  void print();
};

class Peternakan : public Grid<Hewan*>{
public:
  Peternakan(size_t rows, size_t cols);
  Peternakan(Peternakan& other);
  ~Peternakan();
  void print();
};

#endif