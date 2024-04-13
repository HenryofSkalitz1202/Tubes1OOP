#include "Bangunan.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace std;

map<string, Bangunan*> Bangunan::resepBangunan;

Bangunan::Bangunan(int bangunanID, string kodeBangunan, string namaBangunan, int hargaBangunan, map<string, int> listBahan){
    this->setAssetType("BANGUNAN");
    this->setAssetID(bangunanID);
    this->setKodeHuruf(kodeBangunan);
    this->setNamaAsset(namaBangunan);
    this->setPrice(hargaBangunan);
    this->setListBahan(listBahan);
}

Bangunan::~Bangunan(){}

Bangunan::Bangunan(Bangunan& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setPrice(other.getPrice());
    this->setListBahan(other.getListBahan());
}

Bangunan& Bangunan::operator=(const Bangunan& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setPrice(other.price);
    this->setListBahan(other.listBahan);
    return *this;
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

void Bangunan::setListBahan(map<string, int> listBahan){
    this->listBahan.clear();
    for (const auto& pair : listBahan) {
        this->listBahan.insert({pair.first, pair.second});
    }
}

map<string, int> Bangunan::getListBahan(){
    return this->listBahan;
}

//void Bangunan::print(){ //TO DO}