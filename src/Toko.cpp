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