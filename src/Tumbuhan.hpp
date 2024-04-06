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
public:
  ~Tumbuhan();

  void setTumbuhanID(int tumbuhanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaTumbuhan(string namaTumbuhan);
  virtual void setType() = 0;
  void setDurationToHarvest(size_t durationToHarvest);
  void setPrice(int price);
  int getTumbuhanID();
  string getKodeHuruf();
  string getNamaTumbuhan();
  string getType();
  size_t getDurationToHarvest();
  int getPrice();

  bool isReadyToHarvest();
  virtual void harvest() = 0;
};

class FruitPlant :  public Tumbuhan{
public:
  FruitPlant();
  ~FruitPlant();
  FruitPlant(FruitPlant& other);
  FruitPlant& operator=(const FruitPlant& other);

  void setType(){
    this->type = "FRUIT_PLANT";
  }
  void harvest();

};

class MaterialPlant : public Tumbuhan{
public:
  MaterialPlant();
  ~MaterialPlant();
  MaterialPlant(MaterialPlant& other);
  MaterialPlant& operator=(const MaterialPlant& other);
  void setType(){
    this->type = "MATERIAL_PLANT";
  }
  void harvest();
};

#endif