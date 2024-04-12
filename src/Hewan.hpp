#ifndef HEWAN_HPP
#define HEWAN_HPP
#include "Produk.cpp"
#include <string>
#include <vector>
#include <map>
#include "Items.hpp"
using namespace std;

class Hewan : public Asset{
protected:
  string type;
  size_t weightToHarvest;
  int weight;

public:
  static map<string, Hewan*> configHewan;
  ~Hewan();

  void setAssetType(string assetType);
  void setType(string type);
  void setWeightToHarvest(size_t weightToHarvest);
  void setWeight(int weight);

  string getType();
  size_t getWeightToHarvest();
  int getWeight();

  bool isReadyToHarvest();
  virtual void makan(Produk*) = 0;
  vector<Produk*> harvest();
};

class Herbivore : public Hewan{
public:
  Herbivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
  ~Herbivore();
  Herbivore(Herbivore& other);
  Herbivore& operator=(const Herbivore& other);

  void makan(Produk*);
};

class Carnivore : public Hewan{
public:
  Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
  ~Carnivore();
  Carnivore(Carnivore& other);
  Carnivore& operator=(const Carnivore& other);

  void makan(Produk*);
};

class Omnivore : public Hewan{
public:
  Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
  ~Omnivore();
  Omnivore(Omnivore& other);
  Omnivore& operator=(const Omnivore& other);

  void makan(Produk*);
};

#endif