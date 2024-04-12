#include "Herbivore.hpp"

Herbivore::Herbivore(): Hewan() {}

Herbivore::Herbivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price): 
    Hewan(hewanID, kodeHuruf, namaHewan, type, weightToHarvest, 0, price) {
}

Herbivore& Herbivore::operator=(Herbivore& other){
    this->assetID == other.assetID;
    this->kodeHuruf == other.kodeHuruf;
    this->namaAsset == other.namaAsset;
    this->type == other.type;
    this->weightToHarvest == other.weightToHarvest;
    this->weight == other.weight;
    this->price == other.price;
    return *this;
}

Herbivore::~Herbivore(){}

void Herbivore::makan(Produk& produk){
    if (produk.isEdibleHerbivore()){
         this->weight+=produk.getAddedWeight();
    }
    else{
        throw InvalidMakananException();
    }
}
