#include "Hewan.hpp"

Hewan::Hewan(){
    //to do
}

Hewan::Hewan(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price){
    this->hewanID = hewanID;
    this->kodeHuruf = kodeHuruf;
    this->namaHewan = namaHewan;
    this->type = type;
    this->weightToHarvest = weightToHarvest;
    this->weight = weight;
    this->price = price;
}

Hewan::~Hewan(){}

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
void Hewan::setWeight(int weight){
    this->weight = weight;
}
void Hewan::setPrice(int price){
    this->price = price;
}
int Hewan::getHewanID() const{
    return this->hewanID;
}
string Hewan::getKodeHuruf() const{
    return this->kodeHuruf;
}
string Hewan::getNamaHewan() const{
    return this->namaHewan;
}
string Hewan::getType() const{
    return this->type;
}
size_t Hewan::getWeightToHarvest() const{
    return this->weightToHarvest;
}
int Hewan::getWeight() const{
    return this->weight;
}
int Hewan::getPrice() const{
    return this->price;
}
bool Hewan::isReadyToHarvest(){
    return (this->weightToHarvest == this->weight);
}
vector<Produk*> Hewan::harvest(){
    vector<Produk*> harvestedMaterials;

    for (const auto& pair : Produk::configProduk) {
        if (pair.second->getOrigin() == this->namaHewan) {
            harvestedMaterials.push_back(pair.second);
        }
    }

    return harvestedMaterials;
}