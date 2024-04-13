#include "Omnivore.hpp"

Omnivore::Omnivore(): Hewan(){}

Omnivore::Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price) : 
    Hewan(hewanID, kodeHuruf, namaHewan, type, weightToHarvest, 0, price) {
}

Omnivore::~Omnivore(){}

Omnivore& Omnivore::operator=(Omnivore& other){
    this->assetID = other.assetID;
    this->kodeHuruf = other.kodeHuruf;
    this->namaAsset = other.namaAsset;
    this->type = other.type;
    this->weightToHarvest = other.weightToHarvest;
    this->weight = other.weight;
    this->price = other.price;
    return *this;
}

void Omnivore::makan(Produk*& produk){
    if (produk->isEdibleHerbivore() && produk->isEdibleCarnivore()){
        this->weight+=produk->getAddedWeight();
    }
    else{
        throw InvalidMakananException();
    }
}