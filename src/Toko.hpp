#ifndef TOKO_HPP
#define TOKO_HPP

#include "Hewan/Hewan.hpp"
#include "Tumbuhan.hpp"
#include "Bangunan.hpp"
#include "Produk.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Toko {
    private:
        vector<Asset*> listAssetTersedia;
        map<string, int> listJumlahAsset;
        int jumlahBangunan;
        int jumlahProduk;
    public:
        Toko();
        ~Toko();

        Asset* beli(int, int);
        int jual(Asset*, int);

        void setJumlah(string, int);

        void addTersedia(Asset*);
        void removeTersedia(Asset*);

        int getJumlahBangunan() const;
        int getJumlahProduk() const;
        int getJumlah(string);

        void displayToko();
};

#endif