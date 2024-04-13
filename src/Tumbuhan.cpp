#include "Tumbuhan.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace std;
size_t Tumbuhan::current_turn;
map<string, Tumbuhan*> Tumbuhan::configTumbuhan;
//<---------------TUMBUHAN----------------->
Tumbuhan::~Tumbuhan(){}

void Tumbuhan::setAssetType(string assetType){
    try{
        if(assetType != "Tumbuhan"){
            throw TumbuhanFalseTypeException();
        }

        this->assetType = assetType;
    }catch(TumbuhanFalseTypeException& e){
        cout << e.what();
    }
}

void Tumbuhan::setType(string type){
    this->type = type;
}

void Tumbuhan::setDurationToHarvest(size_t durationToHarvest){
    this->duration_to_harvest = duration_to_harvest;
}

void Tumbuhan::setTurnInstantiated(size_t turn_instantiated){
    this->turn_instantiated = turn_instantiated;
}

string Tumbuhan::getType(){
    return this->type;
}

size_t Tumbuhan::getDurationToHarvest(){
    return this->duration_to_harvest;
}

size_t Tumbuhan::getTurnInstantiated(){
    return this->turn_instantiated;
}

bool Tumbuhan::isReadyToHarvest(){
    return (current_turn == this->getTurnInstantiated() + this->getDurationToHarvest());
}

//<---------------FRUIT PLANT----------------->
FruitPlant::FruitPlant(int tumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated){
    this->setAssetType("Tumbuhan");
    this->setAssetID(tumbuhanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaTumbuhan);
    this->setType(type);
    this->setDurationToHarvest(duration_to_harvest);
    this->setPrice(price);
    this->setTurnInstantiated(turn_instantiated);
}

FruitPlant::~FruitPlant(){}

FruitPlant::FruitPlant(FruitPlant& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setType(other.getType());
    this->setDurationToHarvest(other.getDurationToHarvest());
    this->setPrice(other.getPrice());
    this->setTurnInstantiated(other.getTurnInstantiated());
}

FruitPlant& FruitPlant::operator=(const FruitPlant& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setType(other.type);
    this->setDurationToHarvest(other.duration_to_harvest);
    this->setPrice(other.price);
    this->setTurnInstantiated(other.turn_instantiated);
    return *this;
}

vector<Produk*> FruitPlant::harvest(){
    vector<Produk*> harvestedFruits;

    for (const auto& pair : ProductFruit::configProdukFruit) {
        if (pair.second->getOrigin() == this->namaAsset) {
            harvestedFruits.push_back(pair.second);
        }
    }

    return harvestedFruits;
}

//<---------------MATERIAL PLANT----------------->
MaterialPlant::MaterialPlant(int tumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated){
    this->setAssetType("Tumbuhan");
    this->setAssetID(tumbuhanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaTumbuhan);
    this->setType(type);
    this->setDurationToHarvest(duration_to_harvest);
    this->setPrice(price);
    this->setTurnInstantiated(turn_instantiated);
}

MaterialPlant::~MaterialPlant(){}

MaterialPlant::MaterialPlant(MaterialPlant& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setType(other.getType());
    this->setDurationToHarvest(other.getDurationToHarvest());
    this->setPrice(other.getPrice());
    this->setTurnInstantiated(other.getTurnInstantiated());
}

MaterialPlant& MaterialPlant::operator=(const MaterialPlant& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setType(other.type);
    this->setDurationToHarvest(other.duration_to_harvest);
    this->setPrice(other.price);
    this->setTurnInstantiated(other.turn_instantiated);
    return *this;
}

vector<Produk*> MaterialPlant::harvest(){
    vector<Produk*> harvestedMaterials;

    for (const auto& pair : ProductMaterial::configProdukMaterial) {
        if (pair.second->getOrigin() == this->namaAsset) {
            harvestedMaterials.push_back(pair.second);
        }
    }

    return harvestedMaterials;
}