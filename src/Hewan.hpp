#ifndef HEWAN_HPP
#define HEWAN_HPP
#include <string>
using namespace std;

class Hewan{
protected:
  int hewanID;
  string kodeHuruf;
  string namaHewan;
  string type;
  size_t weightToHarvest;
  int price;
public:
  ~Hewan();

  void setHewanID(int hewanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaHewan(string namaHewan);
  virtual void setType() = 0;
  void setWeightToHarvest(size_t weightToHarvest);
  void setPrice(int price);

  int getHewanID();
  string getKodeHuruf();
  string getNamaHewan();
  string getType();
  size_t getWeightToHarvest();
  int getPrice();

  bool isReadyToHarvest();
  virtual void makan() = 0;
  virtual void harvest() = 0;
};

class Herbivore : public Hewan{
public:
  Herbivore();
  ~Herbivore();
  Herbivore(Herbivore& other);
  Herbivore& operator=(Herbivore& other);

  void setType(){
    this->type = "HERBIVORE";
  }

  void makan();
  void harvest();
};

class Carnivore : public Hewan{
public:
  Carnivore();
  ~Carnivore();
  Carnivore(Carnivore& other);
  Carnivore& operator=(Carnivore& other);

  void setType(){
    this->type = "CARNIVORE";
  }

  void makan();
  void harvest();
};

class Omnivore : public Hewan{
public:
  Omnivore();
  ~Omnivore();
  Omnivore(Omnivore& other);
  Omnivore& operator=(Omnivore& other);

  void setType(){
    this->type = "OMNIVORE";
  }

  void makan();
  void harvest();
};
#endif