#include "Asset.hpp"
#include "Exception.hpp"
#include <iostream>
#include <string>

using namespace std;

bool Asset::isThreeLetterCapital(const std::string& str) {
    if (str.size() != 3) {
        return false;
    }

    for (char c : str) {
        if (!std::isupper(c)) {
            return false;
        }
    }

    return true;
}

void Asset::setAssetID(int assetID){
    this->assetID = assetID;
}

void Asset::setKodeHuruf(string kodeHuruf){
    if(Asset::isThreeLetterCapital(kodeHuruf)){
        this->kodeHuruf = kodeHuruf;
    }else{
        cout << "Kode huruf " << kodeHuruf << " is invalid. ";
        throw invalidKodeHurufException();
    }
}

void Asset::setNamaAsset(string namaAsset){
    this->namaAsset = namaAsset;
}

void Asset::setPrice(int price){
    if(price <= 0){
        cout << "Price of " << this->getNamaAsset() << " is set to " << price << ". " << endl;
        throw invalidPriceException();
    }else{
        this->price = price;
    }
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