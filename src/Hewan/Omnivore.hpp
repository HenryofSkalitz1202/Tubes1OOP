#ifndef OMNIVORE_HPP
#define OMNIVORE_HPP
#include "Hewan.hpp"

class Omnivore : public Hewan{
  public:
    Omnivore();
    Omnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
    ~Omnivore();
    Omnivore& operator=(Omnivore& other);
    void makan(Produk&);
};

#endif