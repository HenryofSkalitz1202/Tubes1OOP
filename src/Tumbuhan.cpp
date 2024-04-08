#include "Tumbuhan.hpp"

map<string, Tumbuhan*> Tumbuhan::configTumbuhan;
//<---------------TUMBUHAN----------------->
Tumbuhan::~Tumbuhan(){
    this->kodeHuruf.erase();
    this->namaTumbuhan.erase();
    this->type.erase();
}

void Tumbuhan::setTumbuhanID(int tumbuhanID){
    this->tumbuhanID = tumbuhanID;
}

void Tumbuhan::setKodeHuruf(string kodeHuruf){
    this->kodeHuruf = kodeHuruf;
}

void Tumbuhan::setNamaTumbuhan(string namaTumbuhan){
    this->namaTumbuhan = namaTumbuhan;
}

void Tumbuhan::setType(string type){
    this->type = type;
}

void Tumbuhan::setDurationToHarvest(size_t durationToHarvest){
    this->duration_to_harvest = duration_to_harvest;
}

void Tumbuhan::setPrice(int price){
    this->price = price;
}

void Tumbuhan::setTurnInstantiated(size_t turn_instantiated){
    this->turn_instantiated = turn_instantiated;
}

int Tumbuhan::getTumbuhanID(){
    return this->tumbuhanID;
}

string Tumbuhan::getKodeHuruf(){
    return this->kodeHuruf;
}

string Tumbuhan::getNamaTumbuhan(){
    return this->namaTumbuhan;
}

string Tumbuhan::getType(){
    return this->type;
}

size_t Tumbuhan::getDurationToHarvest(){
    return this->duration_to_harvest;
}

int Tumbuhan::getPrice(){
    return this->price;
}

size_t Tumbuhan::getTurnInstantiated(){
    return this->turn_instantiated;
}

bool Tumbuhan::isReadyToHarvest(){
    return (current_turn == this->getTurnInstantiated() + this->getDurationToHarvest());
}

//<---------------FRUIT PLANT----------------->
FruitPlant::FruitPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated){
    this->setTumbuhanID(tumbuhanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaTumbuhan(namaTumbuhan);
    this->setType(type);
    this->setDurationToHarvest(duration_to_harvest);
    this->setPrice(price);
    this->setTurnInstantiated(turn_instantiated);
}

FruitPlant::~FruitPlant(){}

FruitPlant::FruitPlant(FruitPlant& other){
    this->setTumbuhanID(other.getTumbuhanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaTumbuhan(other.getNamaTumbuhan());
    this->setType(other.getType());
    this->setDurationToHarvest(other.getDurationToHarvest());
    this->setPrice(other.getPrice());
    this->setTurnInstantiated(other.getTurnInstantiated());
}

FruitPlant& FruitPlant::operator=(const FruitPlant& other){
    this->setTumbuhanID(other.tumbuhanID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaTumbuhan(other.namaTumbuhan);
    this->setType(other.type);
    this->setDurationToHarvest(other.duration_to_harvest);
    this->setPrice(other.price);
    this->setTurnInstantiated(other.turn_instantiated);
}

void harvest(){
    //TO DO
}

//<---------------MATERIAL PLANT----------------->
MaterialPlant::MaterialPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated){
    this->setTumbuhanID(tumbuhanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaTumbuhan(namaTumbuhan);
    this->setType(type);
    this->setDurationToHarvest(duration_to_harvest);
    this->setPrice(price);
    this->setTurnInstantiated(turn_instantiated);
}

MaterialPlant::~MaterialPlant(){}

MaterialPlant::MaterialPlant(MaterialPlant& other){
    this->setTumbuhanID(other.getTumbuhanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaTumbuhan(other.getNamaTumbuhan());
    this->setType(other.getType());
    this->setDurationToHarvest(other.getDurationToHarvest());
    this->setPrice(other.getPrice());
    this->setTurnInstantiated(other.getTurnInstantiated());
}

MaterialPlant& MaterialPlant::operator=(const MaterialPlant& other){
    this->setTumbuhanID(other.tumbuhanID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaTumbuhan(other.namaTumbuhan);
    this->setType(other.type);
    this->setDurationToHarvest(other.duration_to_harvest);
    this->setPrice(other.price);
    this->setTurnInstantiated(other.turn_instantiated);
}

void harvest(){
    //TO DO
}