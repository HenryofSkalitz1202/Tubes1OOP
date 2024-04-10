#include "Asset.hpp"
#include <iostream>
#include <string>

using namespace std;

void Asset::setAssetID(int assetID){
    this->assetID = assetID;
}

void Asset::setKodeHuruf(string kodeHuruf){
    this->kodeHuruf = kodeHuruf;
}

void Asset::setNamaAsset(string namaAsset){
    this->namaAsset = namaAsset;
}

void Asset::setPrice(int price){
    this->price = price;
}

string Asset::getAssetType(){
    return this->assetType;
}

int Asset::getAssetID(){
    return this->assetID;
}

string Asset::getKodeHuruf(){
    return this->kodeHuruf;
}

string Asset::getNamaAsset(){
    return this->namaAsset;
}

int Asset::getPrice(){
    return this->price;
}