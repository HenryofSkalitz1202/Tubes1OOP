#include "Bangunan.hpp"

Bangunan::Bangunan(int bangunanID, string namaBangunan, int hargaBangunan){
    this->bangunanID =  bangunanID;
    this->namaBangunan = namaBangunan;
    this->hargaBangunan = hargaBangunan;
}

Bangunan::~Bangunan(){}

Bangunan::Bangunan(Bangunan& other){
    this->bangunanID = other.bangunanID;
    this->namaBangunan = other.namaBangunan;
    this->hargaBangunan = other.hargaBangunan;
}

Bangunan& Bangunan::operator=(const Bangunan& other){
    this->bangunanID = other.bangunanID;
    this->namaBangunan = other.namaBangunan;
    this->hargaBangunan = other.hargaBangunan;
}

void Bangunan::setAssetType(string assetType){
    this->assetType = "BANGUNAN";
}

void Bangunan::setBangunanID(int bangunanID){
    this->bangunanID = bangunanID;
}

void Bangunan::setNamaBangunan(string namaBangunan){
    this->namaBangunan = namaBangunan;
}

void Bangunan::setHargaBangunan(int hargaBangunan){
    this->hargaBangunan = hargaBangunan;
}

int Bangunan::getBangunanID(){
    return this->bangunanID;
}

string Bangunan::getNamaBangunan(){
    return this->namaBangunan;
}

int Bangunan::getHargaBangunan(){
    return this->hargaBangunan;
}

//void Bangunan::print(){ //TO DO}