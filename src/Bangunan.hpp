#ifndef BANGUNAN_HPP
#define BANGUNAN_HPP
#include "Asset.hpp"
#include <string>

using namespace std;

class Bangunan : public Asset{
protected:
  int bangunanID;
  string namaBangunan;
  int hargaBangunan;
  //static vector<Bahan> resepBangunan;

public:
  Bangunan(int bangunanID, string namaBangunan, int hargaBangunan);
  ~Bangunan();
  Bangunan(Bangunan& other);
  Bangunan& operator=(const Bangunan& other);

  void setAssetType(string assetType);
  void setBangunanID(int bangunanID);
  void setNamaBangunan(string namaBangunan);
  void setHargaBangunan(int hargaBangunan);
  int getBangunanID();
  string getNamaBangunan();
  int getHargaBangunan();
  //void print();
};

#endif