#include "Produk.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;

//<---------------PRODUK----------------->
map<string, Produk*> Produk::configProduk;
Produk::Produk() {}
void Produk::setAssetType(string assetType){
    try{
        if(assetType != "PRODUK"){
            throw ProdukFalseTypeException();
        }

        this->assetType = assetType;
    }catch(ProdukFalseTypeException& e){
        cout << e.what();
    }
}

Produk::~Produk(){}


void Produk::setProdukType(string produkType){
    this->produkType = produkType;
}

void Produk::setOrigin(string origin){
    this->origin = origin;
}

string Produk::getProdukType(){
    return this->produkType;
}

string Produk::getOrigin(){
    return this->origin;
}

int Produk::getAddedWeight(){
    return this->addedWeight;
}

int Produk::getPrice()
{
    return 0;
}

bool Produk::isEdibleHerbivore()
{
    return false;
}

bool Produk::isEdibleCarnivore()
{
    return false;
}

bool Produk::isBuildable()
{
    return false;
}

//<---------------PRODUCT MATERIAL----------------->
map<string, ProductMaterial*> ProductMaterial::configProdukMaterial;

void ProductMaterial::setProdukType(string produkType){
    try{
      if(produkType != "PRODUCT_MATERIAL_PLANT"){
        throw ProductMaterialFalseTypeException();
      }
      Produk::setProdukType(produkType);
    } catch(ProductMaterialFalseTypeException& e){
      cout << e.what();
    }
}

ProductMaterial::ProductMaterial(int produkID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price){
    this->setAssetType("PRODUK");
    this->setAssetID(produkID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaProduk);
    this->setProdukType(produkType);
    this->setOrigin(origin);
    this->setAddedWeight(addedWeight);
    this->setPrice(price);
}
ProductMaterial::~ProductMaterial(){}

ProductMaterial::ProductMaterial(ProductMaterial& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setProdukType(other.getProdukType());
    this->setOrigin(other.getOrigin());
    this->setAddedWeight(other.getAddedWeight());
    this->setPrice(other.getPrice());
}

ProductMaterial& ProductMaterial::operator=(const ProductMaterial& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setProdukType(other.produkType);
    this->setOrigin(other.origin);
    this->setAddedWeight(other.addedWeight);
    this->setPrice(other.price);
    return *this;
}

void ProductMaterial::printProduct(ProductMaterial p){
    cout << "Asset Type: " << p.assetType << endl;
    cout << "Produk ID: " << p.assetID << endl;
    cout << "Kode Huruf: " << p.kodeHuruf << endl;
    cout << "Nama Produk: " << p.namaAsset << endl;
    cout << "Product Type: " << p.produkType << endl;
    cout << "Origin: " << p.origin << endl;
    cout << "Added Weight: " << p.addedWeight << endl;
    cout << "Price: " << p.price << endl;
}
//<---------------PRODUCT FRUIT----------------->
map<string, ProductFruit*> ProductFruit::configProdukFruit;

void ProductFruit::setProdukType(string produkType){
    try{
      if(produkType != "PRODUCT_FRUIT_PLANT"){
        throw ProductFruitFalseTypeException();
      }
      Produk::setProdukType(produkType);
    } catch(ProductFruitFalseTypeException& e){
      cout << e.what();
    }
}

void ProductFruit::setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
}

ProductFruit::ProductFruit(int produkID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price){
    this->setAssetType("PRODUK");
    this->setAssetID(produkID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaProduk);
    this->setProdukType(produkType);
    this->setOrigin(origin);
    this->setAddedWeight(addedWeight);
    this->setPrice(price);
}
ProductFruit::~ProductFruit(){}

ProductFruit::ProductFruit(ProductFruit& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setProdukType(other.getProdukType());
    this->setOrigin(other.getOrigin());
    this->setAddedWeight(other.getAddedWeight());
    this->setPrice(other.getPrice());
}

ProductFruit& ProductFruit::operator=(const ProductFruit& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setProdukType(other.produkType);
    this->setOrigin(other.origin);
    this->setAddedWeight(other.addedWeight);
    this->setPrice(other.price);
    return *this;
}

void ProductFruit::printProduct(ProductFruit p){
    cout << "Asset Type: " << p.assetType << endl;
    cout << "Produk ID: " << p.assetID << endl;
    cout << "Kode Huruf: " << p.kodeHuruf << endl;
    cout << "Nama Produk: " << p.namaAsset << endl;
    cout << "Product Type: " << p.produkType << endl;
    cout << "Origin: " << p.origin << endl;
    cout << "Added Weight: " << p.addedWeight << endl;
    cout << "Price: " << p.price << endl;
}

//<---------------PRODUCT HEWAN----------------->
map<string, ProductHewan*> ProductHewan::configProdukHewan;

void ProductHewan::setProdukType(string produkType){
    try{
      if(produkType != "PRODUCT_ANIMAL"){
        throw ProductHewanFalseTypeException();
      }
      Produk::setProdukType(produkType);
    } catch(ProductHewanFalseTypeException& e){
      cout << e.what();
    }
}

void ProductHewan::setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
}

ProductHewan::ProductHewan(int produkID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price){
    this->setAssetType("PRODUK");
    this->setAssetID(produkID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaProduk);
    this->setProdukType(produkType);
    this->setOrigin(origin);
    this->setAddedWeight(addedWeight);
    this->setPrice(price);
}

ProductHewan::~ProductHewan(){}

ProductHewan::ProductHewan(ProductHewan& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setProdukType(other.getProdukType());
    this->setOrigin(other.getOrigin());
    this->setAddedWeight(other.getAddedWeight());
    this->setPrice(other.getPrice());
}

ProductHewan& ProductHewan::operator=(const ProductHewan& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setProdukType(other.produkType);
    this->setOrigin(other.origin);
    this->setAddedWeight(other.addedWeight);
    this->setPrice(other.price);
    return *this;
}

void ProductHewan::printProduct(ProductHewan p){
    cout << "Asset Type: " << p.assetType << endl;
    cout << "Produk ID: " << p.assetID << endl;
    cout << "Kode Huruf: " << p.kodeHuruf << endl;
    cout << "Nama Produk: " << p.namaAsset << endl;
    cout << "Product Type: " << p.produkType << endl;
    cout << "Origin: " << p.origin << endl;
    cout << "Added Weight: " << p.addedWeight << endl;
    cout << "Price: " << p.price << endl;
}