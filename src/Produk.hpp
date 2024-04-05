#ifndef PRODUK_HPP
#define PRODUK_HPP
#include <string>
using namespace std;

class Produk{
protected:
  int produkID;
  string kodeHuruf;
  string namaProduk;
  string produkType;
  string origin;
  int addedWeight;
  int price;
public:
  Produk();
  Produk(string kodeHuruf, string namaProduk, string origin, int addedWeight, int price);
  ~Produk();
  Produk(Produk& other);
  Produk& operator=(const Produk& other);

  void setProdukID(int produkID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaProduk(string namaProduk);
  virtual void setProdukType() = 0;
  void setOrigin(string origin);
  virtual void setAddedWeight() = 0;
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
  void setProdukType(){
    this->produkType = "PRODUCT_MATERIAL_PLANT";
  }

  void setAddedWeight(){
    this->addedWeight = 0;
    //TO DO: exception kalau weight ga 0 maybe?
  }

  void useProduct();
};

class ProductFruit : public Produk{
private:
  const bool isEdibleHerbivore = true;
  const bool isEdibleCarnivore = false;
  const bool isBuildable = false;

public:
  void setProdukType(){
    this->produkType = "PRODUCT_FRUIT_PLANT";
  }

  void setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
  }

  void useProduct();
};

class ProductHewan : public Produk{
private:
  const bool isEdibleHerbivore = false;
  const bool isEdibleCarnivore = true;
  const bool isBuildable = false;

public:
  void setProdukType(){
    this->produkType = "PRODUCT_ANIMAL";
  }

  void setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
  }

  void useProduct();
};

#endif