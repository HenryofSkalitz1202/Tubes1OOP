#include "Bangunan.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace std;

map<string, Bangunan*> Bangunan::resepBangunan;

Bangunan::Bangunan(int bangunanID, string kodeBangunan, string namaBangunan, int hargaBangunan, map<string, int> listBahan){
    this->setAssetType("BANGUNAN");
    this->setBangunanID(bangunanID);
    this->setKodeBangunan(kodeBangunan);
    this->setNamaBangunan(namaBangunan);
    this->setHargaBangunan(hargaBangunan);
    this->setListBahan(listBahan);
}

Bangunan::~Bangunan(){}

Bangunan::Bangunan(Bangunan& other){
    this->setAssetType(other.getAssetType());
    this->setBangunanID(other.getBangunanID());
    this->setKodeBangunan(other.getKodeBangunan());
    this->setNamaBangunan(other.getNamaBangunan());
    this->setHargaBangunan(other.getHargaBangunan());
    this->setListBahan(other.getListBahan());
}

Bangunan& Bangunan::operator=(const Bangunan& other){
    this->setAssetType(other.assetType);
    this->setBangunanID(other.bangunanID);
    this->setKodeBangunan(other.kodeBangunan);
    this->setNamaBangunan(other.namaBangunan);
    this->setHargaBangunan(other.hargaBangunan);
    this->setListBahan(other.listBahan);
}

void Bangunan::setAssetType(string assetType){
    try{
        if(assetType != "BANGUNAN"){
            throw BangunanFalseTypeException();
        }

        this->assetType = assetType;
    }catch(BangunanFalseTypeException& e){
        cout << e.what();
    }
}

void Bangunan::setBangunanID(int bangunanID){
    this->bangunanID = bangunanID;
}

void Bangunan::setKodeBangunan(string kodeBangunan){
    this->kodeBangunan = kodeBangunan;
}

void Bangunan::setNamaBangunan(string namaBangunan){
    this->namaBangunan = namaBangunan;
}

void Bangunan::setHargaBangunan(int hargaBangunan){
    this->hargaBangunan = hargaBangunan;
}

void Bangunan::setListBahan(map<string, int> listBahan){
    this->listBahan.clear();
    for (const auto& pair : listBahan) {
        this->listBahan.insert({pair.first, pair.second});
    }
}

int Bangunan::getBangunanID(){
    return this->bangunanID;
}

string Bangunan::getKodeBangunan(){
    return this->kodeBangunan;
}

string Bangunan::getNamaBangunan(){
    return this->namaBangunan;
}

int Bangunan::getHargaBangunan(){
    return this->hargaBangunan;
}

map<string, int> Bangunan::getListBahan(){
    return this->listBahan;
}

//void Bangunan::print(){ //TO DO}