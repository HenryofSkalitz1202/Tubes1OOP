#ifndef TUMBUHAN_HPP
#define TUMBUHAN_HPP
#include <string>
#include <map>
#include "Items.hpp"

using namespace std;

class Tumbuhan : public Items {
protected:
  int tumbuhanID;
  //string kodeHuruf;
  string namaTumbuhan;
  //string type;
  size_t duration_to_harvest;
  int price;
  size_t turn_instantiated;
public:
  static size_t current_turn;
  static map<string, Tumbuhan*> configTumbuhan;
  Tumbuhan();
  ~Tumbuhan();

  void setTumbuhanID(int tumbuhanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaTumbuhan(string namaTumbuhan);
  void setType(string type);
  void setDurationToHarvest(size_t durationToHarvest);
  void setPrice(int price);
  void setTurnInstantiated(size_t turn_instantiated);
  int getTumbuhanID();
  //string getKodeHuruf();
  string getNamaTumbuhan();
  //string getType();
  size_t getDurationToHarvest();
  int getPrice();
  size_t getTurnInstantiated();
  void operator=(Tumbuhan& other);
  void operator=(Tumbuhan*& other);
  bool isReadyToHarvest();
  //virtual void harvest() = 0;
};

class FruitPlant :  public Tumbuhan{
public:
  FruitPlant();
  FruitPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~FruitPlant();
  FruitPlant(FruitPlant& other);
  void operator=(FruitPlant& other);
  void operator=(Tumbuhan*& other);
  //void harvest(); //TO DO

};

class MaterialPlant : public Tumbuhan{
public:
  MaterialPlant();
  MaterialPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, string type, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~MaterialPlant();
  MaterialPlant(MaterialPlant& other);
  void operator=(MaterialPlant& other);
  void operator=(Tumbuhan*& other);

  //void harvest(); //TO DO
};

#endif