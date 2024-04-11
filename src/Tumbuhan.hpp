#ifndef TUMBUHAN_HPP
#define TUMBUHAN_HPP
#include "Produk.hpp"
#include <string>
#include <vector>

using namespace std;

class Tumbuhan{
protected:
  int tumbuhanID;
  string kodeHuruf;
  string namaTumbuhan;
  string type;
  size_t duration_to_harvest;
  int price;
  size_t turn_instantiated;
public:
  static size_t current_turn;
  static map<string, Tumbuhan*> configTumbuhan;
  ~Tumbuhan();

  void setTumbuhanID(int tumbuhanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaTumbuhan(string namaTumbuhan);
  void setType(string type);
  void setDurationToHarvest(size_t durationToHarvest);
  void setPrice(int price);
  void setTurnInstantiated(size_t turn_instantiated);
  int getTumbuhanID();
  string getKodeHuruf();
  string getNamaTumbuhan();
  string getType();
  size_t getDurationToHarvest();
  int getPrice();
  size_t getTurnInstantiated();

  bool isReadyToHarvest();
  virtual vector<Produk*> harvest() = 0;
};

class FruitPlant :  public Tumbuhan{
public:
  FruitPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~FruitPlant();
  FruitPlant(FruitPlant& other);
  FruitPlant& operator=(const FruitPlant& other);

  vector<Produk*> harvest(); //TO DO
};

class MaterialPlant : public Tumbuhan{
public:
  MaterialPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~MaterialPlant();
  MaterialPlant(MaterialPlant& other);
  MaterialPlant& operator=(const MaterialPlant& other);

  vector<Produk*> harvest(); //TO DO
};

#endif