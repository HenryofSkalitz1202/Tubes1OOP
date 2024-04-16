#ifndef ASSET_HPP
#define ASSET_HPP
#include <string>

using namespace std;

class Asset{
protected:
  string assetType;
  int assetID;
  string kodeHuruf;
  string namaAsset;
  int price;
public:
  ~Asset(){}
  virtual void setAssetType(string assetType) = 0;
  void setAssetID(int assetID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaAsset(string namaAsset);
  void setPrice(int price);

  string getAssetType();
  int getAssetID();
  string getKodeHuruf();
  string getNamaAsset();
  int getPrice();

  Asset& operator=(const Asset*& other);
};

#endif