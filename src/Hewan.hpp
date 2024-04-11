#ifndef HEWAN_HPP
#define HEWAN_HPP
#include "Produk.hpp"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Hewan{
protected:
  int hewanID;
  string kodeHuruf;
  string namaHewan;
  string type;
  size_t weightToHarvest;
  int price;
  int weight;

public:
  static map<string, Hewan*> configHewan;
  ~Hewan();

  void setHewanID(int hewanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaHewan(string namaHewan);
  void setType(string type);
  void setWeightToHarvest(size_t weightToHarvest);
  void setPrice(int price);
  void setWeight(int weight);

  int getHewanID();
  string getKodeHuruf();
  string getNamaHewan();
  string getType();
  size_t getWeightToHarvest();
  int getPrice();
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

  //bool isHerbivore(const std::string& kodeHuruf);

  void makan(Produk*);
};

class Carnivore : public Hewan{
public:
  Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
  ~Carnivore();
  Carnivore(Carnivore& other);
  Carnivore& operator=(const Carnivore& other);

  //bool isCarnivore(const std::string& kodeHuruf);

  void makan(Produk*);
};

class Omnivore : public Hewan{
public:
  Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
  ~Omnivore();
  Omnivore(Omnivore& other);
  Omnivore& operator=(const Omnivore& other);

  //bool isOmnivore(const std::string& kodeHuruf);

  void makan(Produk*);
};

#endif