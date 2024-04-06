#include "Hewan.hpp"

//<---------------HEWAN----------------->
Hewan::~Hewan(){
    kodeHuruf.erase();
    namaHewan.erase();
    type.erase();
}

void Hewan::setHewanID(int hewanID){
    this->hewanID = hewanID;
}

void Hewan::setKodeHuruf(string kodeHuruf){
    this->kodeHuruf = kodeHuruf;
}

void Hewan::setNamaHewan(string namaHewan){
    this->namaHewan = namaHewan;
}

void Hewan::setWeightToHarvest(size_t weightToHarvest){
    this->weightToHarvest = weightToHarvest;
}

void Hewan::setPrice(int price){
    this->price = price;
}

void Hewan::setWeight(int weight){
    this->weight = weight;
}

int Hewan::getHewanID(){
    return this->hewanID;
}

string Hewan::getKodeHuruf(){
    return this->kodeHuruf;
}

string Hewan::getNamaHewan(){
    return this->namaHewan;
}

string Hewan::getType(){
    return this->type;
}

size_t Hewan::getWeightToHarvest(){
    return this->weightToHarvest;
}

int Hewan::getPrice(){
    return this->price;
}

int Hewan::getWeight(){
    return this->weight;
}

bool Hewan::isReadyToHarvest(){
    if (this->weight == this->weightToHarvest){
        return true;
    }
    return false;
}

//<---------------HERBIVORE----------------->
void Herbivore::setType(){
    this->type = "HERBIVORE";
}

Herbivore::Herbivore(int hewanID, string kodeHuruf, string namaHewan, size_t weightToHarvest, int price){
    this->setHewanID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaHewan(namaHewan);
    this->Herbivore::setType();
    this->setWeightToHarvest(weightToHarvest);
    this->setPrice(price);
    this->setWeight(0);
}

Herbivore::~Herbivore(){}

Herbivore::Herbivore(Herbivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}
  
Herbivore& Herbivore::operator=(Herbivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

  void makan();
  void harvest();

//<---------------CARNIVORE----------------->
void Carnivore::setType(){
    this->type = "CARNIVORE";
}

Carnivore::Carnivore(int hewanID, string kodeHuruf, string namaHewan, size_t weightToHarvest, int price){
    this->setHewanID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaHewan(namaHewan);
    this->Carnivore::setType();
    this->setWeightToHarvest(weightToHarvest);
    this->setPrice(price);
    this->setWeight(0);
}
  
Carnivore::~Carnivore(){}

Carnivore::Carnivore(Carnivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

Carnivore& Carnivore::operator=(Carnivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

  void makan();
  void harvest();

//<---------------OMNIVORE----------------->
void Omnivore::setType(){
   this->type = "OMNIVORE";
}

Omnivore::Omnivore(int hewanID, string kodeHuruf, string namaHewan, size_t weightToHarvest, int price){
    this->setHewanID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaHewan(namaHewan);
    this->Omnivore::setType();
    this->setWeightToHarvest(weightToHarvest);
    this->setPrice(price);
    this->setWeight(0);
}

Omnivore::~Omnivore(){}

Omnivore::Omnivore(Omnivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

Omnivore& Omnivore::operator=(Omnivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

  void makan();
  void harvest();