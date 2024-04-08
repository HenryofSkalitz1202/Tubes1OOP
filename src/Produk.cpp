#include "Produk.hpp"
#include <iostream>
using namespace std;

//<---------------PRODUK----------------->
void Produk::setAssetType(){
    this->assetType = "PRODUK";
}

Produk::~Produk(){
    this->kodeHuruf.erase();
    this->namaProduk.erase();
    this->origin.erase();
}

void Produk::setProdukID(int produkID){
    this->produkID = produkID;
}

void Produk::setKodeHuruf(string kodeHuruf){
    this->kodeHuruf = kodeHuruf;
}

void Produk::setNamaProduk(string namaProduk){
    this->namaProduk = namaProduk;
}

void Produk::setOrigin(string origin){
    this->origin = origin;
}

void Produk::setPrice(int price){
    this->price = price;
}

int Produk::getProdukID(){
    return this->produkID;
}

string Produk::getKodeHuruf(){
    return this->kodeHuruf;
}

string Produk::getNamaProduk(){
    return this->namaProduk;
}

string Produk::getOrigin(){
    return this->origin;
}

int Produk::getAddedWeight(){
    return this->addedWeight;
}

int Produk::getPrice(){
    return this->price;
}

//<---------------PRODUCT MATERIAL----------------->
ProductMaterial::ProductMaterial(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price){
    this->setProdukID(produkID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaProduk(namaProduk);
    this->setProdukType();
    this->setOrigin(origin);
    this->setAddedWeight(addedWeight);
    this->setPrice(price);
}
ProductMaterial::~ProductMaterial(){}

ProductMaterial::ProductMaterial(ProductMaterial& other){
    this->setProdukID(other.getProdukID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaProduk(other.getNamaProduk());
    this->setProdukType();
    this->setOrigin(other.getOrigin());
    this->setAddedWeight(other.getAddedWeight());
    this->setPrice(other.getPrice());
}

ProductMaterial& ProductMaterial::operator=(const ProductMaterial& other){
    this->setProdukID(other.produkID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaProduk(other.namaProduk);
    this->setProdukType();
    this->setOrigin(other.origin);
    this->setAddedWeight(other.addedWeight);
    this->setPrice(other.price);
}

void ProductMaterial::printProduct(ProductMaterial p){
    cout << "Asset Type: " << p.assetType << endl;
    cout << "Produk ID: " << p.produkID << endl;
    cout << "Nama Produk: " << p.namaProduk << endl;
    cout << "Product Type: " << p.produkType << endl;
    cout << "Origin: " << p.origin << endl;
    cout << "Added Weight: " << p.addedWeight << endl;
    cout << "Price: " << p.price << endl;
}
//<---------------PRODUCT FRUIT----------------->
void ProductFruit::setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
}

ProductFruit::ProductFruit(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price){
    this->setProdukID(produkID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaProduk(namaProduk);
    this->setProdukType();
    this->setOrigin(origin);
    this->setAddedWeight(addedWeight);
    this->setPrice(price);
}
ProductFruit::~ProductFruit(){}

ProductFruit::ProductFruit(ProductFruit& other){
    this->setProdukID(other.getProdukID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaProduk(other.getNamaProduk());
    this->setProdukType();
    this->setOrigin(other.getOrigin());
    this->setAddedWeight(other.getAddedWeight());
    this->setPrice(other.getPrice());
}

ProductFruit& ProductFruit::operator=(const ProductFruit& other){
    this->setProdukID(other.produkID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaProduk(other.namaProduk);
    this->setProdukType();
    this->setOrigin(other.origin);
    this->setAddedWeight(other.addedWeight);
    this->setPrice(other.price);
}

void ProductFruit::printProduct(ProductFruit p){
    cout << "Asset Type: " << p.assetType << endl;
    cout << "Produk ID: " << p.produkID << endl;
    cout << "Nama Produk: " << p.namaProduk << endl;
    cout << "Product Type: " << p.produkType << endl;
    cout << "Origin: " << p.origin << endl;
    cout << "Added Weight: " << p.addedWeight << endl;
    cout << "Price: " << p.price << endl;
}

//<---------------PRODUCT HEWAN----------------->
void ProductHewan::setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
}

ProductHewan::ProductHewan(int ProdukID, string kodeHuruf, string namaProduk, string produkType, string origin, int addedWeight, int price){
    this->setProdukID(produkID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaProduk(namaProduk);
    this->setProdukType();
    this->setOrigin(origin);
    this->setAddedWeight(addedWeight);
    this->setPrice(price);
}
ProductHewan::~ProductHewan(){}

ProductHewan::ProductHewan(ProductHewan& other){
    this->setProdukID(other.getProdukID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaProduk(other.getNamaProduk());
    this->setProdukType();
    this->setOrigin(other.getOrigin());
    this->setAddedWeight(other.getAddedWeight());
    this->setPrice(other.getPrice());
}

ProductHewan& ProductHewan::operator=(const ProductHewan& other){
    this->setProdukID(other.produkID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaProduk(other.namaProduk);
    this->setProdukType();
    this->setOrigin(other.origin);
    this->setAddedWeight(other.addedWeight);
    this->setPrice(other.price);
}

void ProductHewan::printProduct(ProductHewan p){
    cout << "Asset Type: " << p.assetType << endl;
    cout << "Produk ID: " << p.produkID << endl;
    cout << "Nama Produk: " << p.namaProduk << endl;
    cout << "Product Type: " << p.produkType << endl;
    cout << "Origin: " << p.origin << endl;
    cout << "Added Weight: " << p.addedWeight << endl;
    cout << "Price: " << p.price << endl;
}