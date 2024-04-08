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
  int weight;

public:
  ~Hewan();

  void setHewanID(int hewanID);
  void setKodeHuruf(string kodeHuruf);
  void setNamaHewan(string namaHewan);
  virtual void setType() = 0;
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
  virtual void makan() = 0;
  virtual void harvest() = 0;
};

class Herbivore : public Hewan{
public:
  Herbivore(int hewanID, string kodeHuruf, string namaHewan, size_t weightToHarvest, int price);
  ~Herbivore();
  Herbivore(Herbivore& other);
  Herbivore& operator=(const Herbivore& other);

  void setType();
  bool isHerbivore(const std::string& kodeHuruf);

  void makan();
  void harvest();
};

class Carnivore : public Hewan{
public:
  Carnivore(int hewanID, string kodeHuruf, string namaHewan, size_t weightToHarvest, int price);
  ~Carnivore();
  Carnivore(Carnivore& other);
  Carnivore& operator=(const Carnivore& other);

  void setType();
  bool isCarnivore(const std::string& kodeHuruf);

  void makan();
  void harvest();
};

class Omnivore : public Hewan{
public:
  Omnivore(int hewanID, string kodeHuruf, string namaHewan, size_t weightToHarvest, int price);
  ~Omnivore();
  Omnivore(Omnivore& other);
  Omnivore& operator=(const Omnivore& other);

  void setType();
  bool isOmnivore(const std::string& kodeHuruf);

  void makan();
  void harvest();
};

#endif