#include "Produk.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;

map<string, string> Produk::cekHewan;
map<string, string> Produk::cekMaterialPlant;
map<string, string> Produk::cekFruitPlant;

//<---------------PRODUK----------------->
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
    this->setKodeHuruf(kodeHuruf); //dah di handle di asset
    this->setNamaAsset(namaProduk); //bebas

    this->setProdukType(produkType); //udah pasti bener karna dicek di Controller

    if(Produk::cekMaterialPlant.find(origin) == Produk::cekMaterialPlant.end()){
        cout << namaProduk << " originates from " << origin << " which is not recognized as MaterialPlant. ";
        throw productMaterialNotFromMaterialPlantException();
    }
    this->setOrigin(origin);

    if(addedWeight != 0){
        cout << namaProduk << " has an added weight of " << addedWeight << ". ";
        throw productMaterialFalseAddedWeightException();
    }
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

    if(Produk::cekFruitPlant.find(origin) == Produk::cekFruitPlant.end()){
        cout << namaProduk << " originates from " << origin << " which is not recognized as FruitPlant. ";
        throw productFruitNotFromFruitPlantException();
    }
    this->setOrigin(origin);

    if(addedWeight <= 0){
        cout << namaProduk << " has an added weight of " << addedWeight << ". ";
        throw productFruitFalseAddedWeightException();
    }
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

    if(Produk::cekHewan.find(origin) == Produk::cekHewan.end()){
        cout << namaProduk << " originates from " << origin << " which is not recognized as Hewan. ";
        throw productHewanNotFromHewanException();
    }
    this->setOrigin(origin);

    if(addedWeight <= 0){
        cout << namaProduk << " has an added weight of " << addedWeight << ". ";
        throw productHewanFalseAddedWeightException();
    }
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