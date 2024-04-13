#include "Controller.hpp"
#include "Exception.hpp"
#include "input.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>

vector<Pemain*> Controller::players;
map<string, int> Toko::catalogPrice;
map<string, int> Toko::catalogBangunan;
map<string, int> Toko::catalogProduk;
vector<string> Toko::catalogHewan;
vector<string> Toko::catalogTumbuhan;

Controller::Controller()
{
    this->current_player_index = 0;
    this->turn_number = 0;
    this->game_over = false;
}

Controller::~Controller()
{
    for (size_t i = 0; i < this->players.size(); i++)
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
    map<string, int> mp_bahan;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        ProductMaterial* produkMaterialPtr = nullptr;
        ProductFruit* produkFruitPtr = nullptr;
        ProductHewan* produkHewanPtr = nullptr;
        if(str_arr[3] == "PRODUCT_MATERIAL_PLANT"){
            produkMaterialPtr = new ProductMaterial(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_material.insert({str_arr[2], produkMaterialPtr});
            Toko::catalogPrice.insert({str_arr[2], std::stoi(str_arr[6])});
            Toko::catalogProduk.insert({str_arr[2], 0});
        }else if(str_arr[3] == "PRODUCT_FRUIT_PLANT"){
            produkFruitPtr = new ProductFruit(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_fruit.insert({str_arr[1], produkFruitPtr});
            Toko::catalogPrice.insert({str_arr[1], std::stoi(str_arr[6])});
            Toko::catalogProduk.insert({str_arr[1], 0});
        }else if(str_arr[3] == "PRODUCT_ANIMAL"){
            produkHewanPtr = new ProductHewan(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_hewan.insert({str_arr[1], produkHewanPtr});
            Toko::catalogPrice.insert({str_arr[1], std::stoi(str_arr[6])});
            Toko::catalogProduk.insert({str_arr[1], 0});
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownProductTypeException();
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

    // std::cout << "Map content Material:" << std::endl;
    // for (const auto& pair : ProductMaterial::configProdukMaterial) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    // }

    // std::cout << std::endl;
    // std::cout << "Map content Plant:" << std::endl;
    // for (const auto& pair : ProductFruit::configProdukFruit) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    // }

    // std::cout << std::endl;
    // std::cout << "Map content Hewan:" << std::endl;
    // for (const auto& pair : ProductHewan::configProdukHewan) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    // }
}

void Controller::populateConfigHewan(string filePathHewan){
    FileReader fileReader(filePathHewan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Hewan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Hewan* hewanPtr = nullptr;
        if(str_arr[3] == "HERBIVORE"){
            hewanPtr = new Herbivore(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]));
        }else if(str_arr[3] == "CARNIVORE"){
            hewanPtr = new Carnivore(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]));
        }else if(str_arr[3] == "OMNIVORE"){
            hewanPtr = new Omnivore(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]));
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownAnimalTypeException();
        }
        mp.insert({str_arr[1], hewanPtr});
        Toko::catalogHewan.push_back(str_arr[1]);
        Toko::catalogPrice.insert({str_arr[1], std::stoi(str_arr[5])});
    }

    Hewan::configHewan.clear();
    for (const auto& pair : mp) {
        Hewan::configHewan.insert({pair.first, pair.second});
    }

    // std::cout << "Map content:" << std::endl;
    // for (const auto& pair : Hewan::configHewan) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    // }
}

void Controller::populateConfigTumbuhan(string filePathTumbuhan){
    FileReader fileReader(filePathTumbuhan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Tumbuhan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Tumbuhan* tumbuhanPtr = nullptr;
        if(str_arr[3] == "MATERIAL_PLANT"){
            tumbuhanPtr = new MaterialPlant(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]), Tumbuhan::current_turn);
        }else if(str_arr[3] == "FRUIT_PLANT"){
            tumbuhanPtr = new FruitPlant(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]), Tumbuhan::current_turn);
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownPlantTypeException();
        }
        mp.insert({str_arr[1], tumbuhanPtr});
        Toko::catalogTumbuhan.push_back(str_arr[1]);
        Toko::catalogPrice.insert({str_arr[1], std::stoi(str_arr[5])});
    }

    Tumbuhan::configTumbuhan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Tumbuhan::configTumbuhan.insert({pair.first, pair.second});
    }

    // std::cout << "Map content:" << std::endl;
    // for (const auto& pair : Tumbuhan::configTumbuhan) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    // }
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

        try{
            for(size_t i = 4; i < str_arr.size(); i+=2){
                auto it = ProductMaterial::configProdukMaterial.find(str_arr[i]);
                if (it == ProductMaterial::configProdukMaterial.end()) {
                    cout << "Material " << str_arr[i];
                    throw MaterialBangunanNotProductMaterialException();
                }

                mp_bahan.insert({str_arr[i], std::stoi(str_arr[i+1])});
            }

            bangunanPtr = new Bangunan(std::stoi(str_arr[0]), str_arr[1], str_arr[2], std::stoi(str_arr[3]), mp_bahan);
            mp.insert({str_arr[2], bangunanPtr});
            Toko::catalogBangunan.insert({str_arr[2], 0});
            Toko::catalogPrice.insert({str_arr[2], std::stoi(str_arr[3])});

            // std::cout << "ListBahan:" << std::endl;
            // for (const auto& pair : mp_bahan) {
            //     std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
            // }
            // std::cout << "=====================" << std::endl;
        }catch(MaterialBangunanNotProductMaterialException& e){
            cout << e.what() << endl;
        }catch(exception& e){
            cout << e.what() << endl;
        }
    }

    Bangunan::resepBangunan.clear();
    for (const auto& pair : mp) {
        Bangunan::resepBangunan.insert({pair.first, pair.second});
    }

    // std::cout << "Map content:" << std::endl;
    // for (const auto& pair : Bangunan::resepBangunan) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << ", Bahan: ";
    //     printMap(pair.second->getListBahan());
    // }
}

void Controller::GameConfig(string filePathMisc){
    FileReader fileReader(filePathMisc);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);

    Pemain::uangWin = std::stoi(fileContentarr[0]);
    Pemain::beratWin = std::stoi(fileContentarr[1]);

    vector<string> str_arr_inv = stringToArraySpace(fileContentarr[2]);
    Inventory::inventoryRowSize = std::stoi(str_arr_inv[0]);
    Inventory::inventoryColumnSize = std::stoi(str_arr_inv[1]);

    vector<string> str_arr_lhn = stringToArraySpace(fileContentarr[3]);
    Ladang::lahanRowSize = std::stoi(str_arr_lhn[0]);
    Ladang::lahanColumnSize = std::stoi(str_arr_lhn[1]);

    vector<string> str_arr_pet = stringToArraySpace(fileContentarr[4]);
    Peternakan::peternakanRowSize = std::stoi(str_arr_pet[0]);
    Peternakan::peternakanColumnSize = std::stoi(str_arr_pet[1]);
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
    this->players.push_back(player);
    this->sort_players();
}

Pemain* Controller::get_first_player()
{
    return this->players[0];
}

void Controller::print_players()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        cout << this->players[i]->getUsername() << endl;
    }
}

bool Controller::is_game_over()
{
    return this->game_over;
}

void Controller::is_won()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->getUang() >= Pemain::uangWin && this->players[i]->getBeratBadan() >= Pemain::beratWin)
        {
            cout << this->players[i]->getUsername() << " wins!" << endl;
            this->game_over = true;
            break;
        }
    }
}

void Controller::start_default()
{
    Petani* p1 = new Petani("Petani1", 50, 40);
    Peternak* p2 = new Peternak("Peternak1", 50, 40);
    Walikota* w1 = new Walikota("Walikota", 50, 40);
    this->add_player(w1);
    this->add_player(p1);
    this->add_player(p2);
    this->set_current_player(this->get_first_player());
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

void Controller::next()
{
    this->is_won();
    this->current_player_index = (this->current_player_index + 1) % this->players.size();
    this->current_player = this->players[this->current_player_index];
    this->turn_number++;
    Tumbuhan::current_turn++;
}

void Controller::cetak_penyimpanan(Pemain* player){
    player->getInventory().print();
}

void Controller::pungut_pajak(Walikota* walikota){
    walikota->pungutPajak(Controller::players);
}

void Controller::cetak_ladang(Petani* petani){
    petani->getLadang().print();
}

void Controller::cetak_peternakan(Peternak* peternak){
    peternak->getPeternakan().print();
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

void Controller::beli(Pemain* player, Toko* store){
    player->beliAsset(store);
}

void Controller::jual(Pemain* player){
    player->jualAsset();
}

void Controller::panen(Petani* petani){
    petani->panenTanaman();
}

void Controller::tambah_pemain(Walikota* walikota){
    walikota->tambahAkun(Controller::players);
}