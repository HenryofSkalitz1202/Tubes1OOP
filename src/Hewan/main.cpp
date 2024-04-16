#include "Herbivore.hpp"
#include "Omnivore.hpp"
#include "Carnivore.hpp"

int main(){
    Hewan* hewan1 = new Herbivore(1, "COW", "COW", "HERBIVORE", 10, 500);
    Hewan* hewan2 = new Omnivore(1, "CHK", "CHICKEN", "OMNIVORE", 10, 500);
    Hewan* hewan3 = new Carnivore(3, "SNK", "SNAKE", "CARNIVORE", 10, 50);
    Produk* p = new ProductFruit(5, "APP", "APPLE", "PRODUCT_FRUIT_PLANT", "APPLE_TREE", 4, 8);
    hewan3->printHewan();
    try{
        hewan3->makan(p);
    }
    catch(InvalidMakananException& e){
        cout << e.what() << endl;
    }
    hewan3->printHewan();
}