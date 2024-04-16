#include "Grid.hpp"
#include "Exception.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define YELLOW "\x1B[33m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

template <typename T>
string Grid<T>::calculateKey(int row, int col){
    std::ostringstream oss;
    char key_alphabet = 'A' + col;
    oss << std::setw(2) << std::setfill('0') << row + 1;
    std::string final_key = key_alphabet + oss.str();

    oss.str("");
    oss.clear();

    return final_key;
}

template <typename T>
Grid<T>::Grid(int rows, int cols) : rows(rows), cols(cols) {
    std::ostringstream oss;
    for(int i = 0; i <= this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            std::string kunci = calculateKey(i, j);
            this->data.insert({kunci, nullptr});
        }
    }
}

template <typename T>
void Grid<T>::set(int row, int col, T value){
    // if(row >= this->rows || col >= this->cols) {
    //     cout << "Attempted to set value at position (" << row << ", " << col << ").";
    //     throw outOfBoundsException();
    // }

    // if(this->data[Grid<T>::calculateKey(row, col)] != nullptr){
    //     cout << "Value of grid(" << row << ", " << col << ") is not null. ";
    //     throw insertIntoUnemptyCellException();
    // }

    this->data[Grid<T>::calculateKey(row, col)] = value;
}

template <typename T>
void Grid<T>::setWithKey(string key, T value){
    if(!this->isValidKey(key)) {
        cout << "Attempted to set value with invalid key: " << key;
    }

    if(this->data[key] != nullptr){
        cout << "Value of grid " << key << " is not null. ";
    }
    
    this->data[key] = value;
}

template<typename T>
void Grid<T>::setNull(string key){
    // if(!this->isValidKey(key)){
    //     cout << "Attempted to set value with invalid key: " << key;
    //     throw outOfBoundsException();
    // }

    // if(this->data[key] == nullptr){
    //     throw isAlreadyNullException();
    // }

    this->data[key] = nullptr;
}

template <typename T>
T Grid<T>::get(int row, int col){
    // if(row >= this->rows || col >= this->cols) {
    //     cout << "Attempted to set value at position (" << row << ", " << col << ").";
    //     throw outOfBoundsException();
    // }

    auto it = this->data.find(calculateKey(row, col));
    return it->second;
}

template <typename T>
T Grid<T>::get(string key){
    // if(!this->isValidKey(key)) {
    //     cout << "Attempted to set value with invalid key: " << key;
    //     throw outOfBoundsException();
    // }

    auto it = this->data.find(key);
    return it->second;
}

template <typename T>
int Grid<T>::numRows(){
    return rows;
}

template <typename T>
int Grid<T>::numCols(){
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
    int count = 0;
    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            if (get(i, j) == nullptr) {
                ++count;
            }
        }
    }
    return count;
}

template<typename T>
int Grid<T>::getTotalWorth(){
    int worth = 0;

    for(int row = 0; row < this->numRows(); row++){
        for(int col = 0; col < this->numCols(); col++){
            if(get(row, col) != nullptr){
                worth += get(row, col)->getPrice();
            }
        }
    }

    return worth;
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

template<typename T>
bool Grid<T>::isValidKey(string key){
    if(key.size() != 3){
        return false;
    }

    char colIdentifier = key[0];
    char alphabetUpperBound = 'A' + (this->numCols() - 1);
    if(!std::isupper(colIdentifier)) {
        return false;
    }else if(colIdentifier > alphabetUpperBound || colIdentifier < 'A'){
        return false;
    }

    if(!isdigit(key[1]) || !isdigit(key[2])){
        return false;
    }

    string rowIdentifier = key.substr(1, 2);
    if(std::stoi(rowIdentifier) > this->numRows() || std::stoi(rowIdentifier) <= 0){
        return false;
    }

    return this->data.find(key) != this->data.end();
}
//<---------------INVENTORY----------------->
int Inventory::inventoryRowSize;
int Inventory::inventoryColumnSize;

Inventory::Inventory() : Grid<Asset*>(inventoryRowSize, inventoryColumnSize) {}

Inventory::~Inventory() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            Asset* asset = get(i, j);
            if (asset != nullptr) {
                delete asset;
            }
        }
    }
}

Inventory::Inventory(Inventory& other) : Grid<Asset*>(other.numRows(), other.numCols()) {
    for (int i = 0; i < other.numRows(); ++i) {
        for (int j = 0; j < other.numCols(); ++j) {
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

    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            Asset* asset = get(i, j);
            if (asset != nullptr) {
                delete asset;
            }
        }
    }

    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
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
    if(this->isFull()){
        throw inventoryFullException();
    }
    for (int row = 0; row < this->numRows(); ++row) {
        for (int col = 0; col < this->numCols(); ++col) {
            if (this->data[calculateKey(row, col)] == nullptr) {
                set(row, col, asset);
                return;
            }
        }
    }
}

void Inventory::addItemKey(Asset* asset, string loc) {
    if(this->isFull()){
        throw inventoryFullException();
    }

    setWithKey(loc, asset);
}

void Inventory::findAndRemoveItem(string item_key){
    for(const auto& pair : this->data){
        if(pair.second->getNamaAsset() == item_key){
            this->setNull(pair.first);
            return;
        }
    }
}

int Inventory::getJumlahBangunan(){
    return this->jumlahBangunan;
}

int Inventory::getJumlahProductMaterial(){
    return this->jumlahProductMaterial;
}

int Inventory::getJumlahProductFruit(){
    return this->jumlahProductFruit;
}

int Inventory::getJumlahProductHewan(){
    return this->jumlahProductHewan;
}

int Inventory::getJumlahTumbuhan(){
    return this->jumlahTumbuhan;
}

int Inventory::getJumlahHewan(){
    return this->jumlahHewan;
}

map<string, int> Inventory::rekapMaterial(){
    map<string, int> mapMaterial;
    
    for (const auto& pair : this->data){
        if(dynamic_cast<ProductMaterial*>(pair.second)){
            auto it = mapMaterial.find(pair.second->getNamaAsset());
            if(it != mapMaterial.end()){
                mapMaterial[pair.second->getNamaAsset()]++;
            }else{
                mapMaterial[pair.second->getNamaAsset()] = 1;
            }
        }
    }

    return mapMaterial;
}

void Inventory::rekapInventory() {
    this->jumlahBangunan = 0;
    this->jumlahProductMaterial = 0;
    this->jumlahProductFruit = 0;
    this->jumlahProductHewan = 0;
    this->jumlahTumbuhan = 0;
    this->jumlahHewan = 0;

    for (int i = 0; i < inventoryRowSize; ++i) {
        for (int j = 0; j < inventoryColumnSize; ++j) {
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
                } else if (dynamic_cast<Tumbuhan*>(asset)){
                    this->jumlahTumbuhan++;
                } else if (dynamic_cast<Hewan*>(asset)){
                    this->jumlahHewan++;
                }
            }
        }
    }

    // std::cout << "Inventory Summary:" << endl;
    // std::cout << "Bangunan: " << jumlahBangunan << endl;
    // std::cout << "ProductMaterial: " << jumlahProductMaterial << endl;
    // std::cout << "ProductFruit: " << jumlahProductFruit << endl;
    // std::cout << "ProductHewan: " << jumlahProductHewan << endl;
    // std::cout << "Hewan: " << jumlahHewan << endl;
    // std::cout << "Tumbuhan: " << jumlahTumbuhan << endl;
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
    for (int i = 0; i < other.numRows(); ++i) {
        for (int j = 0; j < other.numCols(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

Ladang& Ladang::operator=(const Ladang& other) {
    if (this == &other)
        return *this;

    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            Tumbuhan* tumbuhan = get(i, j);
            if (tumbuhan != nullptr) {
                delete tumbuhan;
            }
        }
    }

    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            auto it = other.data.find(calculateKey(i, j));
            set(i, j, it->second);
        }
    }
    return *this;
}

Ladang::~Ladang() {
    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            Tumbuhan* tumbuhan = get(i, j);
            if (tumbuhan != nullptr) {
                delete tumbuhan;
            }
        }
    }
}

void Ladang::addItem(Tumbuhan* tumbuhan) {
    if(this->isFull()){
        throw ladangFullException();
    }

    for (int row = 0; row < this->numRows(); ++row) {
        for (int col = 0; col < this->numCols(); ++col) {
            if (this->data[calculateKey(row, col)] == nullptr) {
                set(row, col, tumbuhan);
                return;
            }
        }
    }
}

void Ladang::addItemKey(Tumbuhan* tumbuhan, string loc) {
    if(this->isFull()){
        throw ladangFullException();
    }

    setWithKey(loc, tumbuhan);
}

bool Ladang::isAvailablePanen(){
    for(int row = 0; row < this->numRows(); row++){
        for(int col = 0; col < this->numCols(); col++){
            if(this->get(row, col) != nullptr){
                if(this->get(row, col)->isReadyToHarvest()){
                    return true;
                }
            }
        }
    }

    return false;
}

map<string, int> Ladang::rekapLadang(){
    map<string, int> siapPanen;
    
    for(int row = 0; row < this->numRows(); row++){
        for(int col = 0; col < this->numCols(); col++){
            if(this->get(row, col) != nullptr && this->get(row, col)->isReadyToHarvest()){
                if(siapPanen.find(this->get(row, col)->getKodeHuruf()) != siapPanen.end()){
                    siapPanen[this->get(row, col)->getKodeHuruf()]++;
                }else{
                    siapPanen.insert({this->get(row, col)->getKodeHuruf(), 1});
                }
            }
        }
    }

    return siapPanen;
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
                if(tumbuhan->isReadyToHarvest()){
                    std::cout << GREEN << tumbuhan->getKodeHuruf() << NORMAL;
                }else{
                    std::cout << RED << tumbuhan->getKodeHuruf() << NORMAL;
                }
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
    for (int i = 0; i < other.numRows(); ++i) {
        for (int j = 0; j < other.numCols(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

Peternakan& Peternakan::operator=(const Peternakan& other) {
    if (this == &other)
        return *this;

    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            Hewan* hewan = get(i, j);
            if (hewan != nullptr) {
                delete hewan;
            }
        }
    }

    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            auto it = other.data.find(calculateKey(i, j));
            set(i, j, it->second);
        }
    }
    return *this;
}

Peternakan::~Peternakan() {
    for (int i = 0; i < numRows(); ++i) {
        for (int j = 0; j < numCols(); ++j) {
            Hewan* hewan = get(i, j);
            if (hewan != nullptr) {
                delete hewan;
            }
        }
    }
}

void Peternakan::addItem(Hewan* hewan) {
    if(this->isFull()){
        throw peternakanFullException();
    }

    for (int row = 0; row < this->numRows(); ++row) {
        for (int col = 0; col < this->numCols(); ++col) {
            if (this->data[calculateKey(row, col)] == nullptr) {
                set(row, col, hewan);
                return;
            }
        }
    }
}

void Peternakan::addItemKey(Hewan* hewan, string loc) {
    if(this->isFull()){
        throw peternakanFullException();
    }

    setWithKey(loc, hewan);
}

bool Peternakan::isAvailablePanen(){
    for(int row = 0; row < this->numRows(); row++){
        for(int col = 0; col < this->numCols(); col++){
            if(this->get(row, col) != nullptr){
                if(this->get(row, col)->isReadyToHarvest()){
                    return true;
                }
            }
        }
    }
}

bool Peternakan::hasCarnivore(){
    return this->existCarnivore;
}

bool Peternakan::hasHerbivore(){
    return this->existHerbivore;
}

bool Peternakan::hasOmnivore(){
    return this->existOmnivore;
}

void Peternakan::cekPeternakan(){
    this->existCarnivore = false;
    this->existHerbivore = false;
    this->existOmnivore = false;

    for(const auto& pair : this->data){
        if(dynamic_cast<Carnivore*>(pair.second)){
            this->existCarnivore = true;
        }else if(dynamic_cast<Herbivore*>(pair.second)){
            this->existHerbivore = true;
        }else if(dynamic_cast<Omnivore*>(pair.second)){
            this->existOmnivore = true;
        }

        if(this->existCarnivore && this->existHerbivore && this->existOmnivore){
            return;
        }
    }
}


std::map<std::string, int> Peternakan::rekapPeternakan() {
    std::map<std::string, int> siapPanen;
    
    for(int row = 0; row < this->numRows(); row++){
        for(int col = 0; col < this->numCols(); col++){
            if(this->get(row, col) != nullptr && this->get(row, col)->isReadyToHarvest()){
                if(siapPanen.find(this->get(row, col)->getKodeHuruf()) != siapPanen.end()){
                    siapPanen[this->get(row, col)->getKodeHuruf()]++;
                }else{
                    siapPanen.insert({this->get(row, col)->getKodeHuruf(), 1});
                }
            }
        }
    }

    return siapPanen;
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
                if(hewan->isReadyToHarvest()){
                    std::cout << GREEN << hewan->getKodeHuruf() << NORMAL;
                }else{
                    std::cout << RED << hewan->getKodeHuruf() << NORMAL;
                }
            } else {
                std::cout << "   ";
            }
            std::cout << " | ";
        }
        std::cout << "  " << std::endl;
    }
    printBorder(this->cols);
}