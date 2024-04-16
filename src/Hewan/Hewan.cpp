#include "Hewan.hpp"

map<string, Hewan*> Hewan::configHewan;

Hewan::Hewan(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price){
    this->setAssetType("HEWAN");
    this->setAssetID(hewanID);
    this->setKodeHuruf(kodeHuruf);
    this->setNamaAsset(namaHewan);
    this->setPrice(price);
    this->setType(type);
    this->setWeightToHarvest(weightToHarvest);
    this->setWeight(weight);
}

Hewan::~Hewan(){}

void Hewan::setAssetType(string assetType){
    try{
        if(assetType != "HEWAN"){
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

string Hewan::getType() const{
    return this->type;
}
size_t Hewan::getWeightToHarvest() const{
    return this->weightToHarvest;
}
int Hewan::getWeight() const{
    return this->weight;
}

bool Hewan::isReadyToHarvest(){
    return (this->weightToHarvest == this->weight);
}
vector<Produk*> Hewan::harvest(){
    vector<Produk*> harvestedMaterials;

    for (const auto& pair : Produk::configProduk) {
        if (pair.second->getOrigin() == this->namaAsset) {
            harvestedMaterials.push_back(pair.second);
        }
    }

    return harvestedMaterials;
}
void Hewan::printHewan(){
    cout << "Name: " << this->namaAsset << endl;
    cout << "Price: " << this->price << endl;
    cout << "Type: " << this->type << endl;
    cout << "Weight to harvest: " << this->weightToHarvest << endl;
    cout << "Weight: " << this->weight << endl;
}