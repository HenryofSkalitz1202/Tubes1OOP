#include "Carnivore.hpp"

Carnivore::Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price): 
    Hewan(hewanID, kodeHuruf, namaHewan, type, weightToHarvest, weight, price) {
}

Carnivore& Carnivore::operator=(Carnivore& other){
    this->assetID = other.assetID;
    this->kodeHuruf = other.kodeHuruf;
    this->namaAsset = other.namaAsset;
    this->type = other.type;
    this->weightToHarvest = other.weightToHarvest;
    this->weight = other.weight;
    this->price = other.price;
    return *this;
}

Carnivore::~Carnivore(){}

void Carnivore::makan(Produk* produk){
    if (produk->getProdukType() == "PRODUCT_ANIMAL"){
         this->weight+=produk->getAddedWeight();
    }
    else{
        throw InvalidMakananException();
    }
}