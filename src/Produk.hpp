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
  static map<string, Produk> configProduk;
public:
  ~Produk();

  void setAssetType();
  void setProdukID(int produkID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaProduk(string namaProduk);
  virtual void setProdukType() = 0;
  void setOrigin(string origin);
  virtual void setAddedWeight(int addedWeight) = 0;
  void setPrice(int price);
  int getProdukID();
  string getKodeHuruf();
  string getNamaProduk();
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
  ProductMaterial(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price);
  ~ProductMaterial();
  ProductMaterial(ProductMaterial& other);
  ProductMaterial& operator=(const ProductMaterial& other);

  void setProdukType(){
    this->produkType = "PRODUCT_MATERIAL_PLANT";
  }

  void setAssetType(){
    Produk::setAssetType();
  }

  void setAddedWeight(int addedWeight){
    this->addedWeight = 0;
    //TO DO: exception kalau weight ga 0 maybe?
  }

  void useProduct(){};
  void printProduct(ProductMaterial p);
};

class ProductFruit : public Produk{
private:
  const bool isEdibleHerbivore = true;
  const bool isEdibleCarnivore = false;
  const bool isBuildable = false;

public:
  ProductFruit(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price);
  ~ProductFruit();
  ProductFruit(ProductFruit& other);
  ProductFruit& operator=(const ProductFruit& other);

  void setAssetType(){
    Produk::setAssetType();
  }

  void setProdukType(){
    this->produkType = "PRODUCT_FRUIT_PLANT";
  }

  void setAddedWeight(int addedWeight);

  void useProduct(){};
  void printProduct(ProductFruit p);
};

class ProductHewan : public Produk{
private:
  const bool isEdibleHerbivore = false;
  const bool isEdibleCarnivore = true;
  const bool isBuildable = false;

public:
  ProductHewan(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price);
  ~ProductHewan();
  ProductHewan(ProductHewan& other);
  ProductHewan& operator=(const ProductHewan& other);
  void setAssetType(){
    Produk::setAssetType();
  }

  void setProdukType(){
    this->produkType = "PRODUCT_ANIMAL";
  }

  void setAddedWeight(int addedWeight);

  void useProduct(){};
  void printProduct(ProductHewan p);
};

#endif