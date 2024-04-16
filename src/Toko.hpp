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
  static map<string, string> catalogProdukFruitNama;
  static map<string, string> catalogProdukHewanNama;
  static vector<string> catalogHewan;
  static map<string, string> catalogHewanNama;
  static vector<string> catalogTumbuhan;
  static map<string, string> catalogTumbuhanNama;

  map<string, int> rekapToko();
  int getCheapest();
  int findCheapest();
};

#endif