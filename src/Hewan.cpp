#include "Hewan.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;

map<string, Hewan*> Hewan::configHewan;

//<---------------HEWAN----------------->
Hewan::~Hewan(){}

void Hewan::setAssetType(string assetType){
    try{
        if(assetType != "Hewan"){
            throw HewanFalseTypeException();
        }

        this->assetType = assetType;
    }catch(HewanFalseTypeException& e){
        cout << e.what();
    }
}

void Hewan::setType(string type){
    this->type = type;
}

void Hewan::setWeightToHarvest(size_t weightToHarvest){
    this->weightToHarvest = weightToHarvest;
}

void Hewan::setWeight(int weight){
    this->weight = weight;
}

string Hewan::getType(){
    return this->type;
}

size_t Hewan::getWeightToHarvest(){
    return this->weightToHarvest;
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
        if (pair.second->getOrigin() == this->namaAsset) {
            harvestedMaterials.push_back(pair.second);
        }
    }

    return harvestedMaterials;
}

//<---------------HERBIVORE----------------->
Herbivore::Herbivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price){
    this->setAssetType("Hewan");
    this->setAssetID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaHewan);
    this->setType(type);
    this->setWeightToHarvest(weightToHarvest);
    this->setPrice(price);
    this->setWeight(0);
}

Herbivore::~Herbivore(){}

Herbivore::Herbivore(Herbivore& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setType(other.getType());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}
  
Herbivore& Herbivore::operator=(const Herbivore& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setType(other.type);
    this->setWeightToHarvest(other.weightToHarvest);
    this->setPrice(other.price);
    this->setWeight(other.weight);

    return *this;
}

void Herbivore::makan(Produk* pakan){
    ProductFruit* fruit = dynamic_cast<ProductFruit*>(pakan);
    if (fruit){
        this->weight += fruit->getAddedWeight();
    } else {
        cout << "Herbivore is fed " << pakan->getNamaAsset() << " which is not of ProductFruit type. ";
    }
}

//<---------------CARNIVORE----------------->
Carnivore::Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price){
    this->setAssetType("Hewan");
    this->setAssetID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaHewan);
    this->setType(type);
    this->setWeightToHarvest(weightToHarvest);
    this->setPrice(price);
    this->setWeight(0);
}
  
Carnivore::~Carnivore(){}

Carnivore::Carnivore(Carnivore& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setType(other.getType());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

Carnivore& Carnivore::operator=(const Carnivore& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setType(other.type);
    this->setWeightToHarvest(other.weightToHarvest);
    this->setPrice(other.price);
    this->setWeight(other.weight);

    return *this;
}

void Carnivore::makan(Produk* pakan){
    ProductHewan* hewan = dynamic_cast<ProductHewan*>(pakan);
    if (hewan){
        this->weight += hewan->getAddedWeight();
    } else {
        cout << "Carnivore is fed " << pakan->getNamaAsset() << " which is not of ProductHewan type. ";
    }
}

//<---------------OMNIVORE----------------->

Omnivore::Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price){
    this->setAssetType("Hewan");
    this->setAssetID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaHewan);
    this->setType(type);
    this->setWeightToHarvest(weightToHarvest);
    this->setPrice(price);
    this->setWeight(0);
}

Omnivore::~Omnivore(){}

Omnivore::Omnivore(Omnivore& other){
    this->setAssetType(other.getAssetType());
    this->setAssetID(other.getAssetID());
    this->setKodeHuruf(other.getKodeHuruf());
    this->setNamaAsset(other.getNamaAsset());
    this->setType(other.getType());
    this->setWeightToHarvest(other.getWeightToHarvest());
    this->setPrice(other.getPrice());
    this->setWeight(other.getWeight());
}

Omnivore& Omnivore::operator=(const Omnivore& other){
    this->setAssetType(other.assetType);
    this->setAssetID(other.assetID);
    this->setKodeHuruf(other.kodeHuruf);
    this->setNamaAsset(other.namaAsset);
    this->setType(other.type);
    this->setWeightToHarvest(other.weightToHarvest);
    this->setPrice(other.price);
    this->setWeight(other.weight);

    return *this;
}

void Omnivore::makan(Produk* pakan){
    ProductHewan* hewan = dynamic_cast<ProductHewan*>(pakan);
    if (hewan){
        this->weight += hewan->getAddedWeight();
    } else{
        ProductFruit* fruit = dynamic_cast<ProductFruit*>(pakan);
        if(fruit){
            this->weight += fruit->getAddedWeight();
        } else{
            cout << "Omnivore is fed " << pakan->getNamaAsset() << " which is neither of ProductFruit nor ProductHewan type. ";
        }
    }
}