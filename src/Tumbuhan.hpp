#ifndef TUMBUHAN_HPP
#define TUMBUHAN_HPP
#include "Produk.hpp"
#include <string>
#include <vector>

using namespace std;

class Tumbuhan : public Asset{
protected:
  string type;
  int duration_to_harvest;
  int turn_instantiated;
public:
  static int current_turn;
  static map<string, Tumbuhan*> configTumbuhan;
  ~Tumbuhan();

  void setAssetType(string assetType);
  void setTumbuhanType(string type);
  void setDurationToHarvest(int durationToHarvest);
  void setTurnInstantiated(int turn_instantiated);
  string getTumbuhanType();
  int getDurationToHarvest();
  int getTurnInstantiated();

  bool isReadyToHarvest();
  virtual vector<Produk*> harvest() = 0;
};

class FruitPlant :  public Tumbuhan{
public:
  FruitPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, int durationToHarvest, int price);
  ~FruitPlant();
  FruitPlant(FruitPlant& other);
  FruitPlant& operator=(const FruitPlant& other);

  vector<Produk*> harvest();
};

class MaterialPlant : public Tumbuhan{
public:
  MaterialPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, int durationToHarvest, int price);
  ~MaterialPlant();
  MaterialPlant(MaterialPlant& other);
  MaterialPlant& operator=(const MaterialPlant& other);

  vector<Produk*> harvest();
};

#endif