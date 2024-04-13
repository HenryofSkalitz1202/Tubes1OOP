#ifndef TOKO_HPP
#define TOKO_HPP

#include "Hewan/Hewan.hpp"
#include "Tumbuhan.hpp"
#include "Bangunan.hpp"
#include "Produk.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Toko {
    private:
        vector<Asset*> listAssetTersedia;
        unordered_map<string, int> listJumlahAsset;
        int jumlahBangunan;
        int jumlahProduk;
    public:
        Toko();
        Toko(vector<Bangunan*>, vector<Produk*>, vector<Hewan*>, vector<Tumbuhan*>);
        ~Toko();

        Asset* beli(int, int);
        int jual(Asset*, int);

        void setJumlah(Asset*, int);

        void addTersedia(Asset*);
        void removeTersedia(Asset*);

        int getJumlahBangunan() const;
        int getJumlahProduk() const;

        void displayToko();
};

#endif