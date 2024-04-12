#ifndef GRID_HPP
#define GRID_HPP
#include "Exception.hpp"
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
  //int available_capacity;

public:
  Grid(size_t rows, size_t cols);

  string calculateKey(size_t row, size_t col);
  void set(size_t row, size_t col, T value);
  void setWithKey(string key, T value);
  void setNull(string key);

  T get(size_t row, size_t col);
  T get(string key);
  size_t numRows();
  size_t numCols();
  int countAvailableCapacity();

  bool isEmpty();
  bool isFull();
  bool isValidKey(string key);

  virtual void addItem(T item) = 0;
  virtual void addItemKey(T item, string loc) = 0;
  void printLexicalOrder(int n);
  void printBorder(int n);
  virtual void print() = 0;
};

class Inventory : public Grid<Asset*>{
private:
  int jumlahBangunan;
  int jumlahProductMaterial;
  int jumlahProductFruit;
  int jumlahProductHewan;
public:
  static int inventoryRowSize;
  static int inventoryColumnSize;

  Inventory();
  Inventory(Inventory& other);
  ~Inventory();
  Inventory& operator=(const Inventory& other);

  void addItem(Asset*);
  void addItemKey(Asset*, string loc);
  bool hasType(string type);
  void rekapInventory();
  void print();
};

class Ladang : public Grid<Tumbuhan*>{
public:
  static int lahanRowSize;
  static int lahanColumnSize;

  Ladang();
  Ladang(Ladang& other);
  ~Ladang();
  Ladang& operator=(const Ladang& other);

  void addItem(Tumbuhan*);
  void addItemKey(Tumbuhan*, string loc);

  bool isAvailablePanen();
  map<string, int> rekapLadang();
  void print();
};

class Peternakan : public Grid<Hewan*>{
public:
  static int peternakanRowSize;
  static int peternakanColumnSize;
  Peternakan();
  Peternakan(Peternakan& other);
  ~Peternakan();
  Peternakan& operator=(const Peternakan& other);

  void addItem(Hewan*);
  void addItemKey(Hewan*, string loc);

  bool isAvailablePanen();
  map<string, int> rekapPeternakan();
  void print();
};

#endif