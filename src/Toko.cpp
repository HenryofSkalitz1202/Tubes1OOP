#include "Toko.hpp"
#include <iostream>
#include <string>

using namespace std;

Toko::Toko(){
    for(auto& pair : Toko::catalogBangunan){
        pair.second += 5;
    }

    for(auto& pair : Toko::catalogProduk){
        pair.second += 5;
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
            gudangToko.insert({pair.first, pair.second});
        }
    }
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