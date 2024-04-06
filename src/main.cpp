#include "Pemain.hpp"
#include <iostream>

int Pemain::beratWin = 50;
int Pemain::uangWin = 40;
int Pemain::defaultBerat = 69;
int Pemain::defaultUang = 100;

#include <iostream>
#include <iomanip> // for std::setw

void printBorder(int n) {
    for(int i = 0; i < n; i++) {
        std::cout << "+-----";
    }
    std::cout << "+" << std::endl;
}

int main() {
    printBorder(4);
}
