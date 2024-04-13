#include "Omnivore.hpp"

Omnivore::Omnivore(): Hewan(){}
Omnivore::Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price) : 
    Hewan(hewanID, kodeHuruf, namaHewan, type, weightToHarvest, 0, price) {
}
Omnivore::~Omnivore(){}

void Omnivore::makan(Produk*& produk){
    if (produk->isEdibleHerbivore() && produk->isEdibleCarnivore()){
        this->weight+=produk->getAddedWeight();
    }
    else{
        throw InvalidMakananException();
    }
}