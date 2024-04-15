#include "Tumbuhan.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace std;
int Tumbuhan::current_turn;
map<string, Tumbuhan*> Tumbuhan::configTumbuhan;
//<---------------TUMBUHAN----------------->
Tumbuhan::~Tumbuhan(){}

void Tumbuhan::setAssetType(string assetType){
    try{
        if(assetType != "TUMBUHAN"){
            throw TumbuhanFalseTypeException();
        }

        this->assetType = assetType;
    }catch(TumbuhanFalseTypeException& e){
        cout << e.what();
    }
}

void Tumbuhan::setTumbuhanType(string type){
    this->type = type;
}

void Tumbuhan::setDurationToHarvest(int durationToHarvest){
    if(durationToHarvest <= 0){
        cout << "Duration to harvest of " << this->getNamaAsset() << " is set to " << durationToHarvest << ". " << endl;
        throw invalidDurationToHarvestException();
    }
    this->duration_to_harvest = durationToHarvest;
}

void Tumbuhan::setTurnInstantiated(int turn_instantiated){
    this->turn_instantiated = turn_instantiated;
}

string Tumbuhan::getTumbuhanType(){
    return this->type;
}

int Tumbuhan::getDurationToHarvest(){
    return this->duration_to_harvest;
}

int Tumbuhan::getTurnInstantiated(){
    return this->turn_instantiated;
}

bool Tumbuhan::isReadyToHarvest(){
    return (Tumbuhan::current_turn >= this->getTurnInstantiated() + this->getDurationToHarvest());
}

//<---------------FRUIT PLANT----------------->
FruitPlant::FruitPlant(int tumbuhanID, string kodeHuruf, string namaTumbuhan, string type, int durationToHarvest, int price){
    this->setAssetType("TUMBUHAN");
    this->setAssetID(tumbuhanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaTumbuhan);
    this->setTumbuhanType(type);
    this->setDurationToHarvest(durationToHarvest);
    this->setPrice(price);
    this->setTurnInstantiated(Tumbuhan::current_turn);
}

FruitPlant::~FruitPlant(){}

FruitPlant::FruitPlant(FruitPlant& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setTumbuhanType(other.getTumbuhanType());
    this->setDurationToHarvest(other.getDurationToHarvest());
    this->setPrice(other.getPrice());
    this->setTurnInstantiated(other.getTurnInstantiated());
}

FruitPlant& FruitPlant::operator=(const FruitPlant& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setTumbuhanType(other.type);
    this->setDurationToHarvest(other.duration_to_harvest);
    this->setPrice(other.price);
    this->setTurnInstantiated(other.turn_instantiated);
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
MaterialPlant::MaterialPlant(int tumbuhanID, string kodeHuruf, string namaTumbuhan, string type, int durationToHarvest, int price){
    this->setAssetType("TUMBUHAN");
    this->setAssetID(tumbuhanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaTumbuhan);
    this->setTumbuhanType(type);
    this->setDurationToHarvest(durationToHarvest);
    this->setPrice(price);
    this->setTurnInstantiated(Tumbuhan::current_turn);
}

MaterialPlant::~MaterialPlant(){}

MaterialPlant::MaterialPlant(MaterialPlant& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setTumbuhanType(other.getTumbuhanType());
    this->setDurationToHarvest(other.getDurationToHarvest());
    this->setPrice(other.getPrice());
    this->setTurnInstantiated(other.getTurnInstantiated());
}

MaterialPlant& MaterialPlant::operator=(const MaterialPlant& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setTumbuhanType(other.type);
    this->setDurationToHarvest(other.duration_to_harvest);
    this->setPrice(other.price);
    this->setTurnInstantiated(other.turn_instantiated);
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