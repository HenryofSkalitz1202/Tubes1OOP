#include "Controller.hpp"
#include "Exception.hpp"
#include "input.cpp"
#include "Simpan.cpp"
#include "Muat.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>

vector<Pemain*> Controller::players;
map<string, int> Toko::catalogPrice;
map<string, int> Toko::catalogBangunan;
map<string, int> Toko::catalogProduk;
map<string, string> Toko::catalogProdukFruitNama;
map<string, string> Toko::catalogProdukHewanNama;
vector<string> Toko::catalogHewan;
map<string, string> Toko::catalogHewanNama;
vector<string> Toko::catalogTumbuhan;
map<string, string> Toko::catalogTumbuhanNama;
map<string, string> cekHewan;
map<string, string> cekMaterialPlant;
map<string, string> cekFruitPlant;

Controller::Controller()
{
    this->current_player_index = 0;
    this->turn_number = 0;
    this->game_over = false;
    Tumbuhan::current_turn = this->turn_number;
}

Controller::~Controller()
{
    for (int i = 0; i < this->players.size(); i++)
    {
        delete this->players[i];
    }
}

vector<string> Controller::stringToArrayEnter(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, '\n')) {
        result.push_back(token);
    }
    return result;
}

vector<string> Controller::stringToArraySpace(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

vector<string> Controller::stringToArrayDot(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, '.')) {
        result.push_back(token);
    }
    return result;
}

int Controller::custom_stoi(const std::string& str) {
    int result = 0;
    bool negative = false;
    
    int i = 0;
    if (str[0] == '-') {
        negative = true;
        ++i;
    }

    for (; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            throw invalidStoiException();
        }
    }

    if (negative) {
        result = -1 * result;
    }

    return result;
}

void Controller::printMap(const std::map<std::string, int>& myMap) {
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void Controller::populateConfigProduk(string filePathProduk){
    FileReader fileReader(filePathProduk);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, ProductMaterial*> mp_material;
    map<string, ProductFruit*> mp_fruit;
    map<string, ProductHewan*> mp_hewan;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);

        if(str_arr.size() < 7){
            cout << "On " << filePathProduk << ": " << endl;
            throw missingDataException();
        }else if(str_arr.size() > 7){
            cout << "On " << filePathProduk << ": " << endl;
            throw UnexpectedDataException();
        }


        ProductMaterial* produkMaterialPtr = nullptr;
        ProductFruit* produkFruitPtr = nullptr;
        ProductHewan* produkHewanPtr = nullptr;
        if((mp_material.find(str_arr[2]) == mp_material.end()) && (mp_fruit.find(str_arr[1]) == mp_fruit.end()) && (mp_hewan.find(str_arr[1]) == mp_hewan.end())){
            if(str_arr[3] == "PRODUCT_MATERIAL_PLANT"){
                produkMaterialPtr = new ProductMaterial(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], Controller::custom_stoi(str_arr[5]), Controller::custom_stoi(str_arr[6]));
                mp_material.insert({str_arr[2], produkMaterialPtr});
                Toko::catalogPrice.insert({str_arr[2], Controller::custom_stoi(str_arr[6])});
                Toko::catalogProduk.insert({str_arr[2], 0});
            }else if(str_arr[3] == "PRODUCT_FRUIT_PLANT"){
                produkFruitPtr = new ProductFruit(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], Controller::custom_stoi(str_arr[5]), Controller::custom_stoi(str_arr[6]));
                mp_fruit.insert({str_arr[1], produkFruitPtr});
                Toko::catalogPrice.insert({str_arr[1], Controller::custom_stoi(str_arr[6])});
                Toko::catalogProduk.insert({str_arr[1], 0});
                Toko::catalogProdukFruitNama.insert({str_arr[2], str_arr[1]});
            }else if(str_arr[3] == "PRODUCT_ANIMAL"){
                produkHewanPtr = new ProductHewan(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], Controller::custom_stoi(str_arr[5]), Controller::custom_stoi(str_arr[6]));
                mp_hewan.insert({str_arr[1], produkHewanPtr});
                Toko::catalogPrice.insert({str_arr[1], Controller::custom_stoi(str_arr[6])});
                Toko::catalogProduk.insert({str_arr[1], 0});
                Toko::catalogProdukHewanNama.insert({str_arr[2], str_arr[1]});
            }else{
                cout << "Type " << str_arr[3];
                throw UnknownProductTypeException();
            }
        }else{
            throw duplicateKeyException();
        }
    }

    ProductMaterial::configProdukMaterial.clear();
    for (const auto& pair : mp_material) {
        ProductMaterial::configProdukMaterial.insert({pair.first, pair.second});
    }

    ProductFruit::configProdukFruit.clear();
    for (const auto& pair : mp_fruit) {
        ProductFruit::configProdukFruit.insert({pair.first, pair.second});
    }

    ProductHewan::configProdukHewan.clear();
    for (const auto& pair : mp_hewan) {
        ProductHewan::configProdukHewan.insert({pair.first, pair.second});
    }
}

void Controller::populateConfigHewan(string filePathHewan){
    FileReader fileReader(filePathHewan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Hewan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);

        if(str_arr.size() < 6){
            cout << "On " << filePathHewan << ": " << endl;
            throw missingDataException();
        }else if(str_arr.size() > 6){
            cout << "On " << filePathHewan << ": " << endl;
            throw UnexpectedDataException();
        }

        Hewan* hewanPtr = nullptr;
        if(mp.find(str_arr[1]) == mp.end()){
            if(str_arr[3] == "HERBIVORE"){
                hewanPtr = new Herbivore(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], Controller::custom_stoi(str_arr[4]), Controller::custom_stoi(str_arr[5]));
            }else if(str_arr[3] == "CARNIVORE"){
                hewanPtr = new Carnivore(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], Controller::custom_stoi(str_arr[4]), Controller::custom_stoi(str_arr[5]));
            }else if(str_arr[3] == "OMNIVORE"){
                hewanPtr = new Omnivore(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], Controller::custom_stoi(str_arr[4]), Controller::custom_stoi(str_arr[5]));
            }else{
                cout << "Type " << str_arr[3];
                throw UnknownAnimalTypeException();
            }
            mp.insert({str_arr[1], hewanPtr});
            Toko::catalogHewan.push_back(str_arr[1]);
            Toko::catalogHewanNama.insert({str_arr[2], str_arr[1]});
            Toko::catalogPrice.insert({str_arr[1], Controller::custom_stoi(str_arr[5])});
        }else{
            throw duplicateKeyException();
        }
    }

    Hewan::configHewan.clear();
    for (const auto& pair : mp) {
        Hewan::configHewan.insert({pair.first, pair.second});
        Produk::cekHewan.insert({pair.second->getNamaAsset(), pair.first});
    }
}

void Controller::populateConfigTumbuhan(string filePathTumbuhan){
    FileReader fileReader(filePathTumbuhan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Tumbuhan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);

        if(str_arr.size() < 6){
            cout << "On " << filePathTumbuhan << ": " << endl;
            throw missingDataException();
        }else if(str_arr.size() > 6){
            cout << "On " << filePathTumbuhan << ": " << endl;
            throw UnexpectedDataException();
        }

        Tumbuhan* tumbuhanPtr = nullptr;
        if(mp.find(str_arr[1]) == mp.end()){
            if(str_arr[3] == "MATERIAL_PLANT"){
                tumbuhanPtr = new MaterialPlant(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], Controller::custom_stoi(str_arr[4]), Controller::custom_stoi(str_arr[5]));
                Produk::cekMaterialPlant.insert({str_arr[2], str_arr[1]});
            }else if(str_arr[3] == "FRUIT_PLANT"){
                tumbuhanPtr = new FruitPlant(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], Controller::custom_stoi(str_arr[4]), Controller::custom_stoi(str_arr[5]));
                Produk::cekFruitPlant.insert({str_arr[2], str_arr[1]});
            }else{
                cout << "Type " << str_arr[3];
                throw UnknownPlantTypeException();
            }
            mp.insert({str_arr[1], tumbuhanPtr});
            Toko::catalogTumbuhan.push_back(str_arr[1]);
            Toko::catalogTumbuhanNama.insert({str_arr[2], str_arr[1]});
            Toko::catalogPrice.insert({str_arr[1], Controller::custom_stoi(str_arr[5])});
        }else{
            throw duplicateKeyException();
        }
    }

    Tumbuhan::configTumbuhan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Tumbuhan::configTumbuhan.insert({pair.first, pair.second});
    }
}

void Controller::populateConfigBangunan(string filePathBangunan){
    FileReader fileReader(filePathBangunan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Bangunan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Bangunan* bangunanPtr = nullptr;
        map<string, int> mp_bahan;

        if(str_arr.size() < 6){
            cout << "On " << filePathBangunan << ": " << endl;
            throw missingDataException();
        }else if(str_arr.size() % 2 == 1){
            cout << "On " << filePathBangunan << ": " << endl;
            throw UnexpectedDataException();
        }

        for(int i = 4; i < str_arr.size(); i+=2){
            auto it = ProductMaterial::configProdukMaterial.find(str_arr[i]);
            if (it == ProductMaterial::configProdukMaterial.end()) {
                cout << "Material " << str_arr[i];
                throw MaterialBangunanNotProductMaterialException();
            }

            if(mp_bahan.find(str_arr[i]) == mp_bahan.end()){
                if(Controller::custom_stoi(str_arr[i+1]) > 0){
                    mp_bahan.insert({str_arr[i], Controller::custom_stoi(str_arr[i+1])});
                }else{
                    cout << "Quantity of material " << str_arr[i] << " is set to " << str_arr[i+1] << "." << endl;
                    throw invalidMaterialQuantityException();
                }
            }else{
                throw duplicateKeyException();
            }
        }

        if(mp.find(str_arr[2]) == mp.end()){
            bangunanPtr = new Bangunan(Controller::custom_stoi(str_arr[0]), str_arr[1], str_arr[2], Controller::custom_stoi(str_arr[3]), mp_bahan);
            mp.insert({str_arr[2], bangunanPtr});
            Toko::catalogBangunan.insert({str_arr[2], 0});
            Toko::catalogPrice.insert({str_arr[2], Controller::custom_stoi(str_arr[3])});
        }else{
            throw duplicateKeyException();
        }
    }

    Bangunan::resepBangunan.clear();
    for (const auto& pair : mp) {
        Bangunan::resepBangunan.insert({pair.first, pair.second});
    }
}

void Controller::GameConfig(string filePathMisc){
    FileReader fileReader(filePathMisc);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    if(fileContentarr.size() < 5){
        cout << "On " << filePathMisc << ": " << endl;
        throw missingDataException();
    }else if(fileContentarr.size() > 5){
        cout << "On " << filePathMisc << ": " << endl;
        throw UnexpectedDataException();
    }

    if(Controller::custom_stoi(fileContentarr[0]) <= Pemain::defaultUang){
        throw uangWinTooLittleException();
    }
    Pemain::uangWin = Controller::custom_stoi(fileContentarr[0]);

    if(Controller::custom_stoi(fileContentarr[1]) <= Pemain::defaultBerat){
        throw beratWinTooLittleException();
    }
    Pemain::beratWin = Controller::custom_stoi(fileContentarr[1]);

    vector<string> str_arr_inv = stringToArraySpace(fileContentarr[2]);
    if(str_arr_inv.size() < 2){
        cout << "On " << filePathMisc << ": " << endl;
        throw missingDataException();
    }else if(str_arr_inv.size() > 2){
        cout << "On " << filePathMisc << ": " << endl;
        throw UnexpectedDataException();
    }

    if(Controller::custom_stoi(str_arr_inv[0]) <= 0 || Controller::custom_stoi(str_arr_inv[1]) <= 0){
        throw inventorySizeInvalidException();
    }else if(Controller::custom_stoi(str_arr_inv[1]) > 26){
        throw SizeUnsupportedException();
    }
    Inventory::inventoryRowSize = Controller::custom_stoi(str_arr_inv[0]);
    Inventory::inventoryColumnSize = Controller::custom_stoi(str_arr_inv[1]);

    vector<string> str_arr_lhn = stringToArraySpace(fileContentarr[3]);
    if(str_arr_lhn.size() < 2){
        cout << "On " << filePathMisc << ": " << endl;
        throw missingDataException();
    }else if(str_arr_lhn.size() > 2){
        cout << "On " << filePathMisc << ": " << endl;
        throw UnexpectedDataException();
    }

    if(Controller::custom_stoi(str_arr_lhn[0]) <= 0 || Controller::custom_stoi(str_arr_lhn[1]) <= 0){
        throw ladangSizeInvalidException();
    }else if(Controller::custom_stoi(str_arr_lhn[1]) > 26){
        throw SizeUnsupportedException();
    }
    Ladang::lahanRowSize = Controller::custom_stoi(str_arr_lhn[0]);
    Ladang::lahanColumnSize = Controller::custom_stoi(str_arr_lhn[1]);

    vector<string> str_arr_pet = stringToArraySpace(fileContentarr[4]);
    if(str_arr_pet.size() < 2){
        cout << "On " << filePathMisc << ": " << endl;
        throw missingDataException();
    }else if(str_arr_pet.size() > 2){
        cout << "On " << filePathMisc << ": " << endl;
        throw UnexpectedDataException();
    }

    if(Controller::custom_stoi(str_arr_pet[0]) <= 0 || Controller::custom_stoi(str_arr_pet[1]) <= 0){
        throw peternakanSizeInvalidException();
    }else if(Controller::custom_stoi(str_arr_pet[1]) > 26){
        throw SizeUnsupportedException();
    }
    Peternakan::peternakanRowSize = Controller::custom_stoi(str_arr_pet[0]);
    Peternakan::peternakanColumnSize = Controller::custom_stoi(str_arr_pet[1]);
}

void Controller::set_current_player(Pemain* player)
{
    this->current_player = player;
}

Pemain* Controller::get_current_player()
{
    return this->current_player;
}

void Controller::print_current_player()
{
    cout << this->current_player->getUsername() << endl;
}

void Controller::sort_players() {
    sort(players.begin(), players.end(), [](Pemain* a, Pemain* b) {
        return a->getUsername() < b->getUsername();
    });
}

void Controller::add_player(Pemain* player)
{
    Controller::players.push_back(player);
    this->sort_players();
}

Pemain* Controller::get_first_player()
{
    return Controller::players[0];
}

void Controller::print_players()
{
    for (int i = 0; i < this->players.size(); i++)
    {
        cout << Controller::players[i]->getUsername() << endl;
    }
}

int Controller::getTurnNumber(){
    return this->turn_number;
}

vector<Pemain*> Controller::getPlayers() {
    return this->players;
}

Toko Controller::getToko(){
    return this->store;
}

map<string, int> Controller::getRekapToko(){
    return this->store.rekapToko();
}

bool Controller::is_game_over()
{
    return this->game_over;
}

void Controller::is_won()
{
    for (int i = 0; i < this->players.size(); i++)
    {
        if (Controller::players[i]->getUang() >= Pemain::uangWin && Controller::players[i]->getBeratBadan() >= Pemain::beratWin)
        {
            cout << Controller::players[i]->getUsername() << " wins!" << endl;
            this->game_over = true;
            break;
        }
    }
}

bool Controller::is_petani(Pemain* player)
{
    return dynamic_cast<Petani*>(player) != nullptr;
}

bool Controller::is_peternak(Pemain* player)
{
    return dynamic_cast<Peternak*>(player) != nullptr;
}

bool Controller::is_walikota(Pemain* player)
{
    return dynamic_cast<Walikota*>(player) != nullptr;
}

bool Controller::isValidCommand(string command, Pemain* player){
    if(command == "NEXT"){
        return true;
    }else if(command == "CETAK_PENYIMPANAN"){
        return true;
    }else if(command == "MAKAN"){
        return true;
    }else if(command == "BELI"){
        return true;
    }else if(command == "JUAL"){
        return true;
    }else if(command == "SIMPAN"){
        return true;
    }else{
        if(dynamic_cast<Walikota*>(player)){
            if(command == "PUNGUT_PAJAK"){
                return true;
            }else if(command == "BANGUN"){
                return true;
            }else if(command == "TAMBAH_PEMAIN"){
                return true;
            }else{
                return false;
            }
        }else if(dynamic_cast<Petani*>(player)){
            if(command == "CETAK_LADANG"){
                return true;
            }else if(command == "TANAM"){
                return true;
            }else if(command == "KASIH_MAKAN"){
                return true;
            }else if(command == "PANEN"){
                return true;
            }else{
                return false;
            }
        }else if(dynamic_cast<Peternak*>(player)){
            if(command == "CETAK_PETERNAKAN"){
                return true;
            }else if(command == "TERNAK"){
                return true;
            }else if(command == "KASIH_MAKAN"){
                return true;
            }else if(command == "PANEN"){
                return true;
            }else{
                return false;
            }
        }
    }
}

void Controller::readCommand(Pemain* player){
    cout << CYAN << "========Available Command========" << NORMAL << endl;
    if(dynamic_cast<Petani*>(player)){
        cout << BLUE << "1. NEXT" << endl;
        cout << "2. CETAK_PENYIMPANAN" << endl;
        cout << "3. MAKAN" << endl;
        cout << "4. CETAK_LADANG" << endl;
        cout << "5. TANAM" << endl;
        cout << "6. PANEN" << endl;
        cout << "7. BELI" << endl;
        cout << "8. JUAL" << endl;
        cout << "9. SIMPAN" << NORMAL << endl;
    }else if(dynamic_cast<Peternak*>(player)){
        cout << BLUE << "1. NEXT" << endl;
        cout << "2. CETAK_PENYIMPANAN" << endl;
        cout << "3. MAKAN" << endl;
        cout << "4. CETAK_PETERNAKAN" << endl;
        cout << "5. TERNAK" << endl;
        cout << "6. PANEN" << endl;
        cout << "7. KASIH_MAKAN" << endl;
        cout << "8. BELI" << endl;
        cout << "9. JUAL" << endl;
        cout << "10. SIMPAN" << NORMAL << endl;
    }else if(dynamic_cast<Walikota*>(player)){
        cout << BLUE << "1. NEXT" << endl;
        cout << "2. CETAK_PENYIMPANAN" << endl;
        cout << "3. MAKAN" << endl;
        cout << "4. PUNGUT_PAJAK" << endl;
        cout << "5. BANGUN" << endl;
        cout << "6. BELI" << endl;
        cout << "7. JUAL" << endl;
        cout << "8. SIMPAN" << endl;
        cout << "9. TAMBAH_PEMAIN" << NORMAL << endl;
    }

    string command;
    bool validCommand = false;
    while(!validCommand){
        command = "";
        cout << "> ";
        cin >> command;

        if(isValidCommand(command, player)){
            validCommand = true;
        }else{
            cout << "\033[1;33mCommand is not recognized! Please try again\n\033[0m" << endl;
        }
    }

    if(command == "NEXT"){
        this->next();
    }else if(command == "CETAK_PENYIMPANAN"){
        this->cetak_penyimpanan(player);
    }else if(command == "PUNGUT_PAJAK"){
        this->pungut_pajak(dynamic_cast<Walikota*>(player));
    }else if(command == "CETAK_LADANG"){
        this->cetak_ladang(dynamic_cast<Petani*>(player));
    }else if(command == "CETAK_PETERNAKAN"){
        this->cetak_peternakan(dynamic_cast<Peternak*>(player));
    }else if(command == "TANAM"){
        this->tanam(dynamic_cast<Petani*>(player));
    }else if(command == "TERNAK"){
        this->ternak(dynamic_cast<Peternak*>(player));
    }else if(command == "BANGUN"){
        this->bangun(dynamic_cast<Walikota*>(player));
    }else if(command == "MAKAN"){
        this->makan(player);
    }else if(command == "KASIH_MAKAN"){
        this->kasih_makan(dynamic_cast<Peternak*>(player));
    }else if(command == "BELI"){
        this->beli(player);
    }else if(command == "JUAL"){
        this->jual(player);
    }else if(command == "PANEN"){
        if(dynamic_cast<Petani*>(player)){
            this->panen(dynamic_cast<Petani*>(player));
        }else if(dynamic_cast<Peternak*>(player)){
            this->panen(dynamic_cast<Peternak*>(player));
        }
    }else if(command == "SIMPAN"){
        this->simpan();
    }else if(command == "TAMBAH_PEMAIN"){
        this->tambah_pemain(dynamic_cast<Walikota*>(player));
    }
}

void Controller::next()
{
    this->is_won();
    this->current_player_index = (this->current_player_index + 1) % this->players.size();
    this->current_player = this->players[this->current_player_index];
    this->turn_number++;
    Tumbuhan::current_turn++;

    cout << "Giliran dilanjut ke " << this->current_player->getUsername() << endl;
}

void Controller::cetak_penyimpanan(Pemain* player){
    player->printInventory();
}

void Controller::pungut_pajak(Walikota* walikota){
    walikota->setUang(walikota->getUang() + walikota->pungutPajak(Controller::players));
}

void Controller::cetak_ladang(Petani* petani){
    petani->printLadang();
}

void Controller::cetak_peternakan(Peternak* peternak){
    peternak->printPeternakan();
}

void Controller::tanam(Petani* petani){
    petani->tanamTanaman();
}

void Controller::ternak(Peternak* peternak){
    peternak->taruhHewan();
}

void Controller::bangun(Walikota* walikota){
    walikota->bangunBangunan();
}

void Controller::makan(Pemain* player){
    player->makan();
}

void Controller::kasih_makan(Peternak* peternak){
    peternak->beriMakan();
}

void Controller::beli(Pemain* player){
    Toko* storePtr = &this->store;
    player->beliAsset(storePtr);
}

void Controller::jual(Pemain* player){
    player->jualAsset();
}

void Controller::panen(Petani* petani){
    petani->panenTanaman();
}

void Controller::panen(Peternak* peternak){
    peternak->panenHewan();
}

void Controller::tambah_pemain(Walikota* walikota){
    Pemain* newPlayer = walikota->tambahAkun(Controller::players);
    this->add_player(newPlayer);

    auto it = std::find(Controller::players.begin(), Controller::players.end(), newPlayer);
    int indexNew = std::distance(Controller::players.begin(), it);
    it = std::find(Controller::players.begin(), Controller::players.end(), walikota);
    int indexWalikota = std::distance(Controller::players.begin(), it);

    if(indexWalikota > indexNew){
        this->current_player_index++;
    }
}

void Controller::muat(string filePathState)
{
    Muat Muat(filePathState, *this);
    Muat.read();

    cout << GREEN << filePathState << " successfully loaded!" << NORMAL << endl;
}

void Controller::simpan(){
    string filepath;
    cout << "Masukkan lokasi berkas state: ";
    cin >> filepath;
    try {
        ofstream SaveFile(filepath);
        if (!SaveFile) {
            throw SavePathNotFoundException();
        }
        SaveFile.close();
        Simpan simpan(filepath, *this);
        simpan.write();

        cout << "Saving to " << filepath << "..." << endl;
        cout << GREEN << "State berhasil disimpan" << NORMAL << endl;
    } catch (SavePathNotFoundException& e) {
        cout << "Saving to " << filepath << "..." << endl;
        cout << e.what() << endl;
    }
}