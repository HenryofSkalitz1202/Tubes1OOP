#include "Grid.hpp"
#include "Exception.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

template <typename T>
string Grid<T>::calculateKey(size_t row, size_t col){
    std::ostringstream oss;
    char key_alphabet = 'A' + col;
    oss << std::setw(2) << std::setfill('0') << row;
    std::string final_key = key_alphabet + oss.str();

    oss.str("");
    oss.clear();

    return final_key;
}

template <typename T>
Grid<T>::Grid(size_t rows, size_t cols) : rows(rows), cols(cols) {
    std::ostringstream oss;
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            std::string kunci = calculateKey(i, j);
            this->data.insert({kunci, nullptr});
        }
    }
}

template <typename T>
void Grid<T>::set(size_t row, size_t col, T value){
    this->data[Grid<T>::calculateKey(row, col)] = value;
}

template <typename T>
T Grid<T>::get(size_t row, size_t col){
    auto it = this->data.find(calculateKey(row, col));
    return it->second;
}

template <typename T>
size_t Grid<T>::numRows(){
    return rows;
}

template <typename T>
size_t Grid<T>::numCols(){
    return cols;
}

template <typename T>
void Grid<T>::printLexicalOrder(int n) {
    char current = 'A';
    int count = 0;

    while (count < n) {
        for(int i = 0; i < 5; i++){
            std::cout << " ";
        }
        
        std::cout << current;
        count++;
        current++;

        if (current > 'Z') {
            current = 'A';
        }
    }
    std::cout << std::endl;
}

template <typename T>
void Grid<T>::printBorder(int n) {
    std::cout << "   ";
    for(int i = 0; i < n; i++) {
        std::cout << "+-----";
    }
    std::cout << "+" << std::endl;
}

//<---------------INVENTORY----------------->
Inventory::Inventory(size_t rows, size_t cols) : Grid<Asset*>(rows, cols) {}


// Copy constructor for Inventory
Inventory::Inventory(Inventory& other) : Grid<Asset*>(other.numRows(), other.numCols()) {
    for (size_t i = 0; i < other.numRows(); ++i) {
        for (size_t j = 0; j < other.numCols(); ++j) {
            Asset* asset = other.get(i, j);
            if (asset != nullptr) {
                if (Produk* produk = dynamic_cast<Produk*>(asset)) {
                    Produk* newProduk = nullptr;
                    if (ProductMaterial* material = dynamic_cast<ProductMaterial*>(produk)) {
                        newProduk = new ProductMaterial(*material);
                    } else if (ProductFruit* fruit = dynamic_cast<ProductFruit*>(produk)) {
                        newProduk = new ProductFruit(*fruit);
                    } else if (ProductHewan* hewan = dynamic_cast<ProductHewan*>(produk)) {
                        newProduk = new ProductHewan(*hewan);
                    }
                    newProduk->setProdukType(produk->getProdukType());
                    set(i, j, newProduk);
                } else if (Bangunan* bangunan = dynamic_cast<Bangunan*>(asset)) {
                    set(i, j, new Bangunan(*bangunan));
                }
            }
        }
    }
}

Inventory::~Inventory() {
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            Asset* asset = get(i, j);
            if (asset != nullptr) {
                delete asset;
            }
        }
    }
}

void Inventory::print() {
    //std::cout << ==============[ LADANG ]==================
    std::cout << " ";
    printLexicalOrder(this->cols);
    for (int i = 0; i < this->rows; ++i) {
        printBorder(this->cols);
        std::cout << std::setw(2) << std::setfill('0') << i+1;

        std::cout << " | ";
        for (int j = 0; j < this->cols; ++j) {
            Asset* asset = get(i, j);
            if (asset != nullptr) {
                std::cout << std::setw(3) << std::setfill('0') << asset->getKodeHuruf();
            } else {
                std::cout << "   ";
            }
            std::cout << " | ";
        }
        std::cout << "  " << std::endl;
    }
    printBorder(this->cols);
}

//<---------------LADANG----------------->
Ladang::Ladang(size_t rows, size_t cols) : Grid<Tumbuhan*>(rows, cols) {}

Ladang::Ladang(Ladang& other) : Grid<Tumbuhan*>(other.numRows(), other.numCols()) {
    for (size_t i = 0; i < other.numRows(); ++i) {
        for (size_t j = 0; j < other.numCols(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

Ladang::~Ladang() {
    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            Tumbuhan* tumbuhan = get(i, j);
            if (tumbuhan != nullptr) {
                delete tumbuhan;
            }
        }
    }
}

void Ladang::print() {
    std::cout << " ";
    printLexicalOrder(this->cols);
    for (int i = 0; i < this->rows; ++i) {
        printBorder(this->cols);
        std::cout << std::setw(2) << std::setfill('0') << i+1;

        std::cout << " | ";
        for (int j = 0; j < this->cols; ++j) {
            Tumbuhan* tumbuhan = get(i, j);
            if (tumbuhan != nullptr) {
                std::cout << std::setw(3) << std::setfill('0') << tumbuhan->getKodeHuruf();
            } else {
                std::cout << "   ";
            }
            std::cout << " | ";
        }
        std::cout << "  " << std::endl;
    }
    printBorder(this->cols);
}
//<---------------PETERNAKAN----------------->
Peternakan::Peternakan(size_t rows, size_t cols) : Grid<Hewan*>(rows, cols) {}

Peternakan::Peternakan(Peternakan& other) : Grid<Hewan*>(other.numRows(), other.numCols()) {
    for (size_t i = 0; i < other.numRows(); ++i) {
        for (size_t j = 0; j < other.numCols(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

Peternakan::~Peternakan() {
    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            Hewan* hewan = get(i, j);
            if (hewan != nullptr) {
                delete hewan;
            }
        }
    }
}

void Peternakan::print() {
    std::cout << " ";
    printLexicalOrder(this->cols);
    for (int i = 0; i < this->rows; ++i) {
        printBorder(this->cols);
        std::cout << std::setw(2) << std::setfill('0') << i+1;

        std::cout << " | ";
        for (int j = 0; j < this->cols; ++j) {
            Hewan* hewan = get(i, j);
            if (hewan != nullptr) {
                std::cout << std::setw(3) << std::setfill('0') << hewan->getKodeHuruf();
            } else {
                std::cout << "   ";
            }
            std::cout << " | ";
        }
        std::cout << "  " << std::endl;
    }
    printBorder(this->cols);
}

// int main() {
//     Inventory inventory(3, 3);

//     Produk* produk1 = new ProductMaterial(1, "A", "Material 1", "PRODUCT_MATERIAL_PLANT", "Origin 1", 100, 50);
//     Produk* produk2 = new ProductFruit(2, "B", "Fruit 1", "PRODUCT_FRUIT_PLANT", "Origin 2", 200, 100);
//     Produk* produk3 = new ProductHewan(3, "C", "Animal 1", "PRODUCT_ANIMAL", "Origin 3", 300, 150);

//     Bangunan* bangunan1 = new Bangunan(1, "D", "Bangunan 1", 500, {{"Bahan1", 10}, {"Bahan2", 20}});
//     Bangunan* bangunan2 = new Bangunan(2, "E", "Bangunan 2", 800, {{"Bahan3", 15}, {"Bahan4", 25}});

//     inventory.set(0, 0, produk1);
//     inventory.set(1, 1, produk2);
//     inventory.set(2, 2, produk3);
//     inventory.set(0, 1, bangunan1);
//     inventory.set(2, 0, bangunan2);

//     inventory.print();

//     Asset* retrievedAsset1 = inventory.get(1, 1);
//     if (retrievedAsset1 != nullptr) {
//         std::cout << "Retrieved Asset at (1, 1): " << retrievedAsset1->getKodeHuruf() << std::endl;
//     } else {
//         std::cout << "No Asset found at (1, 1)" << std::endl;
//     }

//     Asset* retrievedAsset2 = inventory.get(0, 1);
//     if (retrievedAsset2 != nullptr) {
//         std::cout << "Retrieved Asset at (0, 1): " << retrievedAsset2->getKodeHuruf() << std::endl;
//     } else {
//         std::cout << "No Asset found at (0, 1)" << std::endl;
//     }

//     return 0;
// }