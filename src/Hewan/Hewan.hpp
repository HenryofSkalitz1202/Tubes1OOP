#ifndef HEWAN_HPP
#define HEWAN_HPP

#include <vector>
#include <map>
#include <iostream>

#include "../Exception.hpp"
#include "../Produk.hpp"
#include "../Asset.hpp"

using namespace std;

class Hewan: public Asset {
  protected:
    string type;
    size_t weightToHarvest;
    int weight;
  public:
    static map<string, Hewan*> configHewan;

    Hewan(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price);
    ~Hewan();

    // setter
    void setAssetType(string AssetType);
    void setType(string type);
    void setWeightToHarvest(size_t weightToHarvest);
    void setWeight(int weight);

    // getter
    string getType() const;
    size_t getWeightToHarvest() const;
    int getWeight() const;

    bool isReadyToHarvest();
    virtual void makan(Produk*) = 0; 
    vector<Produk*> harvest();
};

#endif