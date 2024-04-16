#include "Toko.hpp"
#include "Produk.hpp"
#include <iostream>
#include <string>

using namespace std;

Toko::Toko(){
    for(auto& pair : Toko::catalogBangunan){
        pair.second += 0;
    }

    for(auto& pair : Toko::catalogProduk){
        pair.second += 0;
    }

    this->cheapestPrice = this->findCheapest();
}

Toko::~Toko(){}

map<string, int> Toko::rekapToko(){
    map<string, int> gudangToko;
    for(const auto& pair : Toko::catalogBangunan){
        if(pair.second > 0){
            gudangToko.insert({pair.first, pair.second});
        }
    }
    for(const auto& pair : Toko::catalogProduk){
        if(pair.second > 0){
            if(ProductHewan::configProdukHewan.find(pair.first) != ProductHewan::configProdukHewan.end()){
                gudangToko.insert({ProductHewan::configProdukHewan[pair.first]->getNamaAsset(), pair.second});
            }else if(ProductFruit::configProdukFruit.find(pair.first) != ProductFruit::configProdukFruit.end()){
                gudangToko.insert({ProductFruit::configProdukFruit[pair.first]->getNamaAsset(), pair.second});
            }else if(ProductMaterial::configProdukMaterial.find(pair.first) != ProductMaterial::configProdukMaterial.end()){
                gudangToko.insert({pair.first, pair.second});
            }
        }
    }

    return gudangToko;
}

int Toko::getCheapest(){
    return this->cheapestPrice;
}

int Toko::findCheapest(){
    int cheapestPrice = 9999;
    
    for(const auto& pair : Toko::catalogPrice){
        if(pair.second < cheapestPrice){
            cheapestPrice = pair.second;
        }
    }

    this->cheapestPrice = cheapestPrice;
    return cheapestPrice;
}