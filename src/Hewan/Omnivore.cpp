#include "Omnivore.hpp"

Omnivore::Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price) : 
    Hewan(hewanID, kodeHuruf, namaHewan, type, weightToHarvest, weight, price) {
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
    if (produk->getProdukType() == "PRODUCT_FRUIT_PLANT" || produk->getProdukType() == "PRODUCT_ANIMAL"){
         this->weight+=produk->getAddedWeight();
    }
    else{
        throw InvalidMakananException();
    }
}