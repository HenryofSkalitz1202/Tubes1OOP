#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP
#include "Hewan.hpp"

class Herbivore : public Hewan{
    public:
        Herbivore(int hewanID, string kodeHuruf, string namaHewan, string type, size_t weightToHarvest, int weight, int price);
        ~Herbivore();
        Herbivore& operator=(Herbivore& other);
        void makan(Produk*&);
    };

#endif