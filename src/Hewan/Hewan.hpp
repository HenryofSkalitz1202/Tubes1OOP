#ifndef HEWAN_HPP
#define HEWAN_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "../Exception.hpp"
#include "../Produk.hpp"
#include "../Asset.hpp"

using namespace std;

// enum class Category{
//     Cow = 1,
//     Sheep = 2,
//     Horse = 3,
//     Rabbit = 4,
//     Snake = 5,
//     Chicken = 6,
//     Duck = 7
// };

class Hewan: public Asset {
  protected:
    string type;
    size_t weightToHarvest;
    int weight;
  public:
    static map<string, Hewan*> configHewan;

    Hewan(); 
    Hewan(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price);
    virtual ~Hewan();

    // setter
    void setAssetType(string AssetType);
    void setType(string type);
    void setWeightToHarvest(size_t weightToHarvest);
    void setWeight(int weight);
    void setPrice(int price);

    // getter
    string getType() const;
    size_t getWeightToHarvest() const;
    int getWeight() const;

    bool isReadyToHarvest();
    virtual void makan(Produk*&) = 0; 
    vector<Produk*> harvest();
};

#endif