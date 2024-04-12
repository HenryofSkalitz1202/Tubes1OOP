#include "Tumbuhan.hpp"

map<string, Tumbuhan*> Tumbuhan::configTumbuhan;
//<---------------TUMBUHAN----------------->
Tumbuhan::Tumbuhan(): Items() {
    this->tumbuhanID = -1;
    this->namaTumbuhan = "-";
    this->duration_to_harvest = -1;
    this->price = -1;
    this->turn_instantiated = -1;
}

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

/*string Tumbuhan::getKodeHuruf(){
    return this->kodeHuruf;
}*/

string Tumbuhan::getNamaTumbuhan(){
    return this->namaTumbuhan;
}

/*string Tumbuhan::getType(){
    return this->type;
}*/

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
    return (1 == this->getTurnInstantiated() + this->getDurationToHarvest());
}

void Tumbuhan::operator=(Tumbuhan& other) {
    this->tumbuhanID = other.tumbuhanID;
    this->namaTumbuhan = other.namaTumbuhan;
    this->type = other.type;
    this->duration_to_harvest = other.duration_to_harvest;
    this->price = other.price;
    this->turn_instantiated = other.turn_instantiated;
}

void Tumbuhan::operator=(Tumbuhan*& other) {
    this->tumbuhanID = other->tumbuhanID;
    this->namaTumbuhan = other->namaTumbuhan;
    this->type = other->type;
    this->duration_to_harvest = other->duration_to_harvest;
    this->price = other->price;
    this->turn_instantiated = other->turn_instantiated;
}
//<---------------FRUIT PLANT----------------->
FruitPlant::FruitPlant() : Tumbuhan(){};

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

void FruitPlant::operator=(FruitPlant& other) {
    this->tumbuhanID = other.tumbuhanID;
    this->namaTumbuhan = other.namaTumbuhan;
    this->type = other.type;
    this->duration_to_harvest = other.duration_to_harvest;
    this->price = other.price;
    this->turn_instantiated = other.turn_instantiated;
}

void FruitPlant::operator=(Tumbuhan*& other) {
    this->tumbuhanID = other->getTumbuhanID();
    this->namaTumbuhan = other->getNamaTumbuhan();
    this->type = other->getType();
    this->duration_to_harvest = other->getDurationToHarvest();
    this->price = other->getPrice();
    this->turn_instantiated = other->getTurnInstantiated();
}

//void FruitPlant::harvest(){
    //TO DO
//}

//<---------------MATERIAL PLANT----------------->
MaterialPlant::MaterialPlant() : Tumbuhan() {};

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

void MaterialPlant::operator=(MaterialPlant& other) {
    this->tumbuhanID = other.tumbuhanID;
    this->namaTumbuhan = other.namaTumbuhan;
    this->type = other.type;
    this->duration_to_harvest = other.duration_to_harvest;
    this->price = other.price;
    this->turn_instantiated = other.turn_instantiated;
}

void MaterialPlant::operator=(Tumbuhan*& other) {
    this->tumbuhanID = other->getTumbuhanID();
    this->namaTumbuhan = other->getNamaTumbuhan();
    this->type = other->getType();
    this->duration_to_harvest = other->getDurationToHarvest();
    this->price = other->getPrice();
    this->turn_instantiated = other->getTurnInstantiated();
}

//void MaterialPlant::harvest(){
    //TO DO
//}