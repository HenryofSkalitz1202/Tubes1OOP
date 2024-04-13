#include "Toko.hpp"
#include <iostream>
#include <string>

using namespace std;

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