#ifndef TOKO_HPP
#define TOKO_HPP
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Toko{
private:
  ~Toko();

public:
  static map<string, int> catalog;
};

#endif