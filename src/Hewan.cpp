#include "Hewan.hpp"
#include <unordered_set>
#include "Exception.hpp"
#include <iostream>
using namespace std;

map<string, Hewan*> Hewan::configHewan;

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

void Hewan::setType(string type){
    this->type = type;
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

vector<Produk*> Hewan::harvest(){
    vector<Produk*> harvestedMaterials;

    for (const auto& pair : ProductHewan::configProdukHewan) {
        if (pair.second->getOrigin() == this->namaHewan) {
            harvestedMaterials.push_back(pair.second);
        }
    }

    return harvestedMaterials;
}

//<---------------HERBIVORE----------------->
// bool Herbivore::isHerbivore(const std::string& kodeHuruf) {
//     static const std::unordered_set<std::string> herbivoreCodes = {
//         "COW", "SHP", "HRS", "RBT"
//     };

//     return herbivoreCodes.find(kodeHuruf) != herbivoreCodes.end();
// }

Herbivore::Herbivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price){
    try{
        // if(!isHerbivore(kodeHuruf)){
        //     throw NotHerbivoreException();
        // }
        this->setHewanID(hewanID);
        this->setKodeHuruf(kodeHuruf);
        this->setNamaHewan(namaHewan);
        this->setType(type);
        this->setWeightToHarvest(weightToHarvest);
        this->setPrice(price);
        this->setWeight(0);
    }catch(NotHerbivoreException& e){
        cout << "Hewan dengan kode " << kodeHuruf << e.what() << endl;
    }
}

Herbivore::~Herbivore(){}

Herbivore::Herbivore(Herbivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setType(other.getType());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}
  
Herbivore& Herbivore::operator=(const Herbivore& other){
    this->setHewanID(other.hewanID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaHewan(other.namaHewan);
    this->setType(other.type);
    this->setWeightToHarvest(other.weightToHarvest);
    this->setPrice(other.price);
    this->setWeight(other.weight);

    return *this;
}

void Herbivore::makan(Produk* pakan){
    try{
        ProductFruit* fruit = dynamic_cast<ProductFruit*>(pakan);
        if (fruit){
            this->weight += fruit->getAddedWeight();
        } else {
            cout << "Herbivore is fed " << pakan->getNamaAsset() << " which is not of ProductFruit type. ";
            throw HerbivoreWrongFoodTypeException();
        }
    }catch(HerbivoreWrongFoodTypeException& e){
        cout << e.what();
    }
}

//<---------------CARNIVORE----------------->
// bool Carnivore::isCarnivore(const std::string& kodeHuruf) {
//     static const std::unordered_set<std::string> carnivoreCodes = {
//         "SNK"
//     };

//     return carnivoreCodes.find(kodeHuruf) != carnivoreCodes.end();
// }

Carnivore::Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price){
    try{
        // if(!isCarnivore(kodeHuruf)){
        //     throw NotCarnivoreException();
        // }
        this->setHewanID(hewanID);
        this->setKodeHuruf(kodeHuruf);
        this->setNamaHewan(namaHewan);
        this->setType(type);
        this->setWeightToHarvest(weightToHarvest);
        this->setPrice(price);
        this->setWeight(0);
    }catch(NotCarnivoreException& e){
        cout << "Hewan dengan kode " << kodeHuruf << e.what() << endl;
    }
}
  
Carnivore::~Carnivore(){}

Carnivore::Carnivore(Carnivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setType(other.getType());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

Carnivore& Carnivore::operator=(const Carnivore& other){
    this->setHewanID(other.hewanID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaHewan(other.namaHewan);
    this->setType(other.type);
    this->setWeightToHarvest(other.weightToHarvest);
    this->setPrice(other.price);
    this->setWeight(other.weight);

    return *this;
}

void Carnivore::makan(Produk* pakan){
    try{
        ProductHewan* hewan = dynamic_cast<ProductHewan*>(pakan);
        if (hewan){
            this->weight += hewan->getAddedWeight();
        } else {
            cout << "Carnivore is fed " << pakan->getNamaAsset() << " which is not of ProductHewan type. ";
            throw CarnivoreWrongFoodTypeException();
        }
    }catch(CarnivoreWrongFoodTypeException& e){
        cout << e.what();
    }
}

//<---------------OMNIVORE----------------->
// bool Omnivore::isOmnivore(const std::string& kodeHuruf) {
//     static const std::unordered_set<std::string> omnivoreCodes = {
//         "CHK", "DCK"
//     };

//     return omnivoreCodes.find(kodeHuruf) != omnivoreCodes.end();
// }

Omnivore::Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price){
    try{
        // if(!isOmnivore(kodeHuruf)){
        //     throw NotOmnivoreException();
        // }
        this->setHewanID(hewanID);
        this->setKodeHuruf(kodeHuruf);
        this->setNamaHewan(namaHewan);
        this->setType(type);
        this->setWeightToHarvest(weightToHarvest);
        this->setPrice(price);
        this->setWeight(0);
    }catch(NotOmnivoreException& e){
        cout << "Hewan dengan kode huruf " << kodeHuruf << e.what();
    }
}

Omnivore::~Omnivore(){}

Omnivore::Omnivore(Omnivore& other){
    this->setHewanID(other.getHewanID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaHewan(other.getNamaHewan());
    this->setType(other.getType());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

Omnivore& Omnivore::operator=(const Omnivore& other){
    this->setHewanID(other.hewanID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaHewan(other.namaHewan);
    this->setType(other.type);
    this->setWeightToHarvest(other.weightToHarvest);
    this->setPrice(other.price);
    this->setWeight(other.weight);

    return *this;
}

void Omnivore::makan(Produk* pakan){
    try{
        ProductHewan* hewan = dynamic_cast<ProductHewan*>(pakan);
        if (hewan){
            this->weight += hewan->getAddedWeight();
        } else{
            ProductFruit* fruit = dynamic_cast<ProductFruit*>(pakan);
            if(fruit){
                this->weight += fruit->getAddedWeight();
            } else{
                cout << "Omnivore is fed " << pakan->getNamaAsset() << " which is neither of ProductFruit nor ProductHewan type. ";
                throw OmnivoreWrongFoodTypeException();
            }
        }
    }catch(OmnivoreWrongFoodTypeException& e){
        cout << e.what();
    }
}