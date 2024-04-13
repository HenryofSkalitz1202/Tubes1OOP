#ifndef TOKO_HPP
#define TOKO_HPP
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Toko{
private:
  ~Toko();
  int cheapestPrice;

public:
  static map<string, int> catalogPrice;
  static map<string, int> catalogBangunan;
  static map<string, int> catalogProduk;
  static vector<string> catalogHewan;
  static vector<string> catalogTumbuhan;

  int getCheapest();
  int findCheapest();
};

#endif