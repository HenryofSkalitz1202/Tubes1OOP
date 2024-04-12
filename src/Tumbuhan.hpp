#ifndef TUMBUHAN_HPP
#define TUMBUHAN_HPP
#include "Produk.hpp"
#include <string>
#include <vector>

using namespace std;

class Tumbuhan : public Asset{
protected:
  string type;
  size_t duration_to_harvest;
  size_t turn_instantiated;
public:
  static size_t current_turn;
  static map<string, Tumbuhan*> configTumbuhan;
  Tumbuhan();
  ~Tumbuhan();

  void setAssetType(string assetType);
  void setType(string type);
  void setDurationToHarvest(size_t durationToHarvest);
  void setTurnInstantiated(size_t turn_instantiated);
  string getType();
  size_t getDurationToHarvest();
  size_t getTurnInstantiated();
  void operator=(Tumbuhan& other);
  void operator=(Tumbuhan*& other);
  bool isReadyToHarvest();
  virtual vector<Produk*> harvest() = 0;
};

class FruitPlant :  public Tumbuhan{
public:
  FruitPlant();
  FruitPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~FruitPlant();
  FruitPlant(FruitPlant& other);
  FruitPlant& operator=(const FruitPlant& other);

  vector<Produk*> harvest();
};

class MaterialPlant : public Tumbuhan{
public:
  MaterialPlant();
  MaterialPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~MaterialPlant();
  MaterialPlant(MaterialPlant& other);
  void operator=(MaterialPlant& other);
  void operator=(Tumbuhan*& other);

  vector<Produk*> harvest();
};

#endif