#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP
#include "Hewan.hpp"
#include <map>


class Carnivore : public Hewan{
     public:
        Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int price);
        Carnivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price);
        ~Carnivore();
        Carnivore& operator=(Carnivore& other);
        void makan(Produk*);
    };

#endif