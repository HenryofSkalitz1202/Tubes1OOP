#ifndef TUMBUHAN_HPP
#define TUMBUHAN_HPP
#include <string>

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
  static size_t current_turn;
public:
  ~Tumbuhan();

  void setTumbuhanID(int tumbuhanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaTumbuhan(string namaTumbuhan);
  virtual void setType() = 0;
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
  virtual void harvest() = 0;
};

class FruitPlant :  public Tumbuhan{
public:
  FruitPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~FruitPlant();
  FruitPlant(FruitPlant& other);
  FruitPlant& operator=(const FruitPlant& other);

  void setType();
  void harvest();

};

class MaterialPlant : public Tumbuhan{
public:
  MaterialPlant(int TumbuhanID, string kodeHuruf, string namaTumbuhan, size_t durationToHarvest, int price, size_t turn_instantiated);
  ~MaterialPlant();
  MaterialPlant(MaterialPlant& other);
  MaterialPlant& operator=(const MaterialPlant& other);
  void setType(){
    this->type = "MATERIAL_PLANT";
  }
  void harvest();
};

#endif