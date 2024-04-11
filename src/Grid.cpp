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
    oss << std::setw(2) << std::setfill('0') << row + 1;
    std::string final_key = key_alphabet + oss.str();

    oss.str("");
    oss.clear();

    return final_key;
}

template <typename T>
Grid<T>::Grid(size_t rows, size_t cols) : rows(rows), cols(cols) {
    std::ostringstream oss;
    for(int i = 0; i <= this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            std::string kunci = calculateKey(i, j);
            this->data.insert({kunci, nullptr});
        }
    }
}

template <typename T>
void Grid<T>::set(size_t row, size_t col, T value){
    try{
        if(this->data[Grid<T>::calculateKey(row, col)] != nullptr){
            cout << "Value of grid(" << row << ", " << col << ") is not null. ";
            throw insertIntoUnemptyCellException();
        }
        this->data[Grid<T>::calculateKey(row, col)] = value;
    } catch(insertIntoUnemptyCellException& e){
        cout << e.what();
    }
}

template <typename T>
void Grid<T>::setWithKey(string key, T value){
    try{
        if(this->data[key] != nullptr){
            cout << "Value of grid " << key << " is not null. ";
            throw insertIntoUnemptyCellException();
        }

        this->data[key] = value;
    } catch(insertIntoUnemptyCellException& e){
        cout << e.what();
    }
}

template <typename T>
T Grid<T>::get(size_t row, size_t col){
    auto it = this->data.find(calculateKey(row, col));
    return it->second;
}

template <typename T>
T Grid<T>::get(string key){
    auto it = this->data.find(key);
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

template<typename T>
int Grid<T>::countAvailableCapacity() {
    size_t count = 0;
    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            if (get(i, j) == nullptr) {
                ++count;
            }
        }
    }
    return count;
}

template<typename T>
bool Grid<T>::isEmpty(){
    if(this->countAvailableCapacity() == (this->rows * this->cols)){
        return true;
    }else{
        return false;
    }
}

template<typename T>
bool Grid<T>::isFull(){
    if(this->countAvailableCapacity() == 0){
        return true;
    }else{
        return false;
    }
}
//<---------------INVENTORY----------------->
int Inventory::inventoryRowSize;
int Inventory::inventoryColumnSize;

Inventory::Inventory() : Grid<Asset*>(inventoryRowSize, inventoryColumnSize) {}

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

Inventory& Inventory::operator=(const Inventory& other) {
    if (this == &other)
        return *this;

    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            Asset* asset = get(i, j);
            if (asset != nullptr) {
                delete asset;
            }
        }
    }

    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            auto it = other.data.find(calculateKey(i, j));
            Asset* asset = it->second;
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
    return *this;
}

void Inventory::addItem(Asset* asset) {
    try{
        if(this->isFull()){
            throw inventoryFullException();
        }
        for (size_t row = 0; row < this->numRows(); ++row) {
            for (size_t col = 0; col < this->numCols(); ++col) {
                if (this->data[calculateKey(row, col)] == nullptr) {
                    set(row, col, asset);
                    return;
                }
            }
        }
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

void Inventory::addItemKey(Asset* asset, string loc) {
    try{
        if(this->isFull()){
            throw inventoryFullException();
        }

        setWithKey(loc, asset);
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

void Inventory::rekapInventory() {
    this->jumlahBangunan = 0;
    this->jumlahProductMaterial = 0;
    this->jumlahProductFruit = 0;
    this->jumlahProductHewan = 0;

    for (size_t i = 0; i < inventoryRowSize; ++i) {
        for (size_t j = 0; j < inventoryColumnSize; ++j) {
            Asset* asset = this->get(i, j);
            
            if (asset) {
                if (dynamic_cast<Bangunan*>(asset)) {
                    this->jumlahBangunan++;
                } else if (dynamic_cast<ProductMaterial*>(asset)) {
                    this->jumlahProductMaterial++;
                } else if (dynamic_cast<ProductFruit*>(asset)) {
                    this->jumlahProductFruit++;
                } else if (dynamic_cast<ProductHewan*>(asset)) {
                    this->jumlahProductHewan++;
                }
            }
        }
    }

    std::cout << "Inventory Summary:" << endl;
    std::cout << "Bangunan: " << jumlahBangunan << endl;
    std::cout << "ProductMaterial: " << jumlahProductMaterial << endl;
    std::cout << "ProductFruit: " << jumlahProductFruit << endl;
    std::cout << "ProductHewan: " << jumlahProductHewan << endl;
}

void Inventory::print() {
    //std::cout << ==============[ PENYIMPANAN ]==================
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
int Ladang::lahanRowSize;
int Ladang::lahanColumnSize;

Ladang::Ladang() : Grid<Tumbuhan*>(lahanRowSize, lahanColumnSize) {}

Ladang::Ladang(Ladang& other) : Grid<Tumbuhan*>(other.numRows(), other.numCols()) {
    for (size_t i = 0; i < other.numRows(); ++i) {
        for (size_t j = 0; j < other.numCols(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

Ladang& Ladang::operator=(const Ladang& other) {
    if (this == &other)
        return *this;

    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            Tumbuhan* tumbuhan = get(i, j);
            if (tumbuhan != nullptr) {
                delete tumbuhan;
            }
        }
    }

    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            auto it = other.data.find(calculateKey(i, j));
            set(i, j, it->second);
        }
    }
    return *this;
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

void Ladang::setJumlahTumbuhan(){
    this->jumlahTumbuhan = this->countAvailableCapacity();
}

int Ladang::getJumlahTumbuhan(){
    return this->jumlahTumbuhan;
}

void Ladang::addItem(Tumbuhan* tumbuhan) {
    try{
        if(this->isFull()){
            throw ladangFullException();
        }
        for (size_t row = 0; row < this->numRows(); ++row) {
            for (size_t col = 0; col < this->numCols(); ++col) {
                if (this->data[calculateKey(row, col)] == nullptr) {
                    set(row, col, tumbuhan);
                    return;
                }
            }
        }
    }catch(ladangFullException& e){
        std::cout << e.what();
    }
}

void Ladang::addItemKey(Tumbuhan* tumbuhan, string loc) {
    try{
        if(this->isFull()){
            throw ladangFullException();
        }

        setWithKey(loc, tumbuhan);
    }catch(ladangFullException& e){
        std::cout << e.what();
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
int Peternakan::peternakanRowSize;
int Peternakan::peternakanColumnSize;

Peternakan::Peternakan() : Grid<Hewan*>(peternakanRowSize, peternakanColumnSize) {}

Peternakan::Peternakan(Peternakan& other) : Grid<Hewan*>(other.numRows(), other.numCols()) {
    for (size_t i = 0; i < other.numRows(); ++i) {
        for (size_t j = 0; j < other.numCols(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

Peternakan& Peternakan::operator=(const Peternakan& other) {
    if (this == &other)
        return *this;

    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            Hewan* hewan = get(i, j);
            if (hewan != nullptr) {
                delete hewan;
            }
        }
    }

    for (size_t i = 0; i < numRows(); ++i) {
        for (size_t j = 0; j < numCols(); ++j) {
            auto it = other.data.find(calculateKey(i, j));
            set(i, j, it->second);
        }
    }
    return *this;
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

void Peternakan::setJumlahHewan(){
    this->jumlahHewan = this->countAvailableCapacity();
}

int Peternakan::getJumlahHewan(){
    return this->jumlahHewan;
}

void Peternakan::addItem(Hewan* hewan) {
    try{
        if(this->isFull()){
            throw peternakanFullException();
        }
        for (size_t row = 0; row < this->numRows(); ++row) {
            for (size_t col = 0; col < this->numCols(); ++col) {
                if (this->data[calculateKey(row, col)] == nullptr) {
                    set(row, col, hewan);
                    return;
                }
            }
        }
    }catch(peternakanFullException& e){
        std::cout << e.what();
    }
}

void Peternakan::addItemKey(Hewan* hewan, string loc) {
    try{
        if(this->isFull()){
            throw peternakanFullException();
        }

        setWithKey(loc, hewan);
    }catch(peternakanFullException& e){
        std::cout << e.what();
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