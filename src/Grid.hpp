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
  int available_capacity;

public:
  Grid(size_t rows, size_t cols);
  string calculateKey(size_t row, size_t col);
  void set(size_t row, size_t col, T value);
  T get(size_t row, size_t col);
  size_t numRows();
  size_t numCols();
  int countAvailableCapacity();
  void printLexicalOrder(int n);
  void printBorder(int n);
  virtual void print() = 0;
};

class Inventory : public Grid<Asset*>{
public:
  static int inventoryRowSize;
  static int inventoryColumnSize;
  // Constructors
  Inventory(size_t rows, size_t cols);
  Inventory(Inventory& other);
  ~Inventory();
  Inventory& operator=(const Inventory& other);
  void print();
};

class Ladang : public Grid<Tumbuhan*>{
public:
  Ladang(size_t rows, size_t cols);
  Ladang(Ladang& other);
  ~Ladang();
  Ladang& operator=(const Ladang& other);
  void print();
};

class Peternakan : public Grid<Hewan*>{
public:
  Peternakan(size_t rows, size_t cols);
  Peternakan(Peternakan& other);
  ~Peternakan();
  Peternakan& operator=(const Peternakan& other);
  void print();
};

#endif