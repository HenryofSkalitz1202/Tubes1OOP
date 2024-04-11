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
  //int available_capacity;

public:
  Grid(size_t rows, size_t cols);

  string calculateKey(size_t row, size_t col);
  void set(size_t row, size_t col, T value);
  T get(size_t row, size_t col);
  size_t numRows();
  size_t numCols();
  int countAvailableCapacity();
  bool isEmpty();
  bool isFull();

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

  void rekapInventory();
  void print();
};

class Ladang : public Grid<Tumbuhan*>{
private:
  int jumlahTumbuhan;
public:
  static int lahanRowSize;
  static int lahanColumnSize;

  Ladang();
  Ladang(Ladang& other);
  ~Ladang();
  Ladang& operator=(const Ladang& other);

  void setJumlahTumbuhan();
  int getJumlahTumbuhan();
  void print();
};

class Peternakan : public Grid<Hewan*>{
private:
  int jumlahHewan;
public:
  static int peternakanRowSize;
  static int peternakanColumnSize;
  Peternakan();
  Peternakan(Peternakan& other);
  ~Peternakan();
  Peternakan& operator=(const Peternakan& other);

  void setJumlahHewan();
  int getJumlahHewan();
  void print();
};

#endif