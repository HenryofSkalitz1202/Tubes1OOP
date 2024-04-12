#ifndef BANGUNAN_HPP
#define BANGUNAN_HPP
#include "Asset.hpp"
#include "Items.hpp"
#include <string>
#include <map>

using namespace std;

class Bangunan : public Asset, public Items {
protected:
  map<string, int> listBahan;

public:
  static map<string, Bangunan*> resepBangunan;
  Bangunan(int bangunanID, string kodeHuruf, string namaBangunan, int hargaBangunan, map<string, int> listBahan);
  ~Bangunan();
  Bangunan(Bangunan& other);
  Bangunan& operator=(const Bangunan& other);

  void setAssetType(string assetType);
  void setListBahan(map<string, int> listBahan);
  map<string, int> getListBahan();
  //void print();
};


#endif