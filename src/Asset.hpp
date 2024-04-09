#ifndef ASSET_HPP
#define ASSET_HPP
#include <string>

using namespace std;

class Asset{
protected:
  string assetType;
public:
  ~Asset(){}

  virtual void setAssetType(string assetType) = 0;
  string getAssetType(){
    return this->assetType;
  }
};

#endif