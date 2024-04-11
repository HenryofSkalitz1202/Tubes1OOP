#ifndef HEWAN_HPP
#define HEWAN_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "../Exception/Exception.hpp"
#include "../Produk.hpp"

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

class Hewan{
  protected:
    int hewanID;
    string kodeHuruf;
    string namaHewan;
    string type;
    size_t weightToHarvest;
    int weight;
    int price;
  public:
    static map<string, Hewan*> configHewan;

    Hewan(); 
    Hewan(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price);
    virtual ~Hewan();

    // setter
    void setHewanID(int hewanID);
    void setKodeHuruf(string kodeHuruf);
    void setNamaHewan(string namaHewan);
    void setType(string type);
    void setWeightToHarvest(size_t weightToHarvest);
    void setWeight(int weight);
    void setPrice(int price);

    // getter
    int getHewanID() const;
    string getKodeHuruf() const;
    string getNamaHewan() const;
    string getType() const;
    size_t getWeightToHarvest() const;
    int getWeight() const;
    int getPrice() const;

    bool isReadyToHarvest();
    virtual void makan(Produk&) = 0; 
    vector<Produk*> harvest();
};

#endif