#ifndef PRODUK_HPP
#define PRODUK_HPP
#include "Asset.hpp"
#include <string>
#include <map>
using namespace std;

class Produk : public Asset{
protected:
  int produkID;
  string kodeHuruf;
  string namaProduk;
  string produkType;
  string origin;
  int addedWeight;
  int price;

public:
  ~Produk();

  void setAssetType(string assetType);
  void setProdukID(int produkID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaProduk(string namaProduk);
  void setProdukType(string produkType);
  void setOrigin(string origin);
  virtual void setAddedWeight(int addedWeight) = 0;
  void setPrice(int price);
  int getProdukID();
  string getKodeHuruf();
  string getNamaProduk();
  string getProdukType();
  string getOrigin();
  int getAddedWeight();
  int getPrice();

  virtual void useProduct() = 0;
};

class ProductMaterial : public Produk{
private:
  const bool isEdibleHerbivore = false;
  const bool isEdibleCarnivore = false;
  const bool isBuildable = true;

public:
  static map<string, ProductMaterial*> configProdukMaterial;

  ProductMaterial(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price);
  ~ProductMaterial();
  ProductMaterial(ProductMaterial& other);
  ProductMaterial& operator=(const ProductMaterial& other);

  void setAssetType(string assetType);
  void setProdukType(string produkType);

  void setAddedWeight(int addedWeight){
    this->addedWeight = 0;
    //TO DO: exception kalau weight ga 0 maybe?
  }

  void useProduct(){}; //TO DO
  void printProduct(ProductMaterial p);
};

class ProductFruit : public Produk{
private:
  const bool isEdibleHerbivore = true;
  const bool isEdibleCarnivore = false;
  const bool isBuildable = false;

public:
  static map<string, ProductFruit*> configProdukFruit;
  ProductFruit(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price);
  ~ProductFruit();
  ProductFruit(ProductFruit& other);
  ProductFruit& operator=(const ProductFruit& other);

  void setAssetType(string assetType);
  void setProdukType(string produkType);
  void setAddedWeight(int addedWeight);

  void useProduct(){}; //TO DO
  void printProduct(ProductFruit p);
};

class ProductHewan : public Produk{
private:
  const bool isEdibleHerbivore = false;
  const bool isEdibleCarnivore = true;
  const bool isBuildable = false;

public:
  static map<string, ProductHewan*> configProdukHewan;
  ProductHewan(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price);
  ~ProductHewan();
  ProductHewan(ProductHewan& other);
  ProductHewan& operator=(const ProductHewan& other);

  void setAssetType(string assetType);
  void setProdukType(string produkType);
  void setAddedWeight(int addedWeight);

  void useProduct(){}; //TO DO
  void printProduct(ProductHewan p);
};

#endif