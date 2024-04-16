#ifndef TOKO_HPP
#define TOKO_HPP
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Toko{
private:
  int cheapestPrice;

public:
  Toko();
  ~Toko();
  
  static map<string, int> catalogPrice;
  static map<string, int> catalogBangunan;
  static map<string, int> catalogProduk;
  static vector<string> catalogHewan;
  static vector<string> catalogTumbuhan;

  map<string, int> rekapToko();
  int getCheapest();
  int findCheapest();
};

#endif