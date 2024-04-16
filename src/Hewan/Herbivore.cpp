#include "Herbivore.hpp"

Herbivore::Herbivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price): 
    Hewan(hewanID, kodeHuruf, namaHewan, type, weightToHarvest, weight, price) {
}

Herbivore& Herbivore::operator=(Herbivore& other){
    this->assetID = other.assetID;
    this->kodeHuruf = other.kodeHuruf;
    this->namaAsset = other.namaAsset;
    this->type = other.type;
    this->weightToHarvest = other.weightToHarvest;
    this->weight = other.weight;
    this->price = other.price;
    return *this;
}

Herbivore::~Herbivore(){}

void Herbivore::makan(Produk*& produk){
    if (produk->getProdukType() == "PRODUCT_FRUIT_PLANT"){
         this->weight+=produk->getAddedWeight();
    }
    else{
        throw InvalidMakananException();
    }
}
