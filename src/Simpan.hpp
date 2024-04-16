#ifndef SIMPAN_HPP
#define SIMPAN_HPP

#include "Controller.hpp"
#include <iostream>
using namespace std;

class Simpan {
    private:
        string filepath;
        Controller& controller;
    public:
        Simpan(string filepath, Controller& controller);
        void write();
        vector<string> inventoryItems(Pemain* player);
        vector<string> ladangItems(Petani* player);
        vector<string> peternakanItems (Peternak* player);
        string calculateKey(size_t row, size_t col);
};

#endif