#include "Pemain.cpp"
#include "input.cpp"
#include "Exception.hpp"
#include "Produk.cpp"
#include "Hewan.cpp"
#include "Tumbuhan.cpp"
#include "Bangunan.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>

int Pemain::defaultBerat = 69;
int Pemain::defaultUang = 100;
size_t Tumbuhan::current_turn = 0;

vector<string> stringToArrayEnter(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, '\n')) {
        result.push_back(token);
    }
    return result;
}

vector<string> stringToArraySpace(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

void printVector(const vector<string>& vec) {
    cout << "<";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << ">" << endl;
}

void populateConfigProduk(string filePathProduk){
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
        }else if(str_arr[3] == "PRODUCT_FRUIT_PLANT"){
            produkFruitPtr = new ProductFruit(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_fruit.insert({str_arr[1], produkFruitPtr});
        }else if(str_arr[3] == "PRODUCT_ANIMAL"){
            produkHewanPtr = new ProductHewan(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_hewan.insert({str_arr[1], produkHewanPtr});
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownProductTypeException();
        }
    }

    ProductMaterial::configProdukMaterial.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp_material) {
        ProductMaterial::configProdukMaterial.insert({pair.first, pair.second});
    }

    ProductFruit::configProdukFruit.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp_fruit) {
        ProductFruit::configProdukFruit.insert({pair.first, pair.second});
    }

    ProductHewan::configProdukHewan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp_hewan) {
        ProductHewan::configProdukHewan.insert({pair.first, pair.second});
    }

    std::cout << "Map content Material:" << std::endl;
    for (const auto& pair : ProductMaterial::configProdukMaterial) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaProduk() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Map content Plant:" << std::endl;
    for (const auto& pair : ProductFruit::configProdukFruit) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaProduk() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Map content Hewan:" << std::endl;
    for (const auto& pair : ProductHewan::configProdukHewan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaProduk() << std::endl;
    }
}

void populateConfigHewan(string filePathHewan){
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
    }

    Hewan::configHewan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Hewan::configHewan.insert({pair.first, pair.second});
    }

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Hewan::configHewan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaHewan() << std::endl;
    }
}

void populateConfigTumbuhan(string filePathTumbuhan){
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
    }

    Tumbuhan::configTumbuhan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Tumbuhan::configTumbuhan.insert({pair.first, pair.second});
    }

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Tumbuhan::configTumbuhan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaTumbuhan() << std::endl;
    }
}

void populateConfigBangunan(string filePathBangunan){
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
            mp.insert({str_arr[1], bangunanPtr});

            std::cout << "ListBahan:" << std::endl;
            for (const auto& pair : mp_bahan) {
                std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
            }
            std::cout << "=====================" << std::endl;
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

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Bangunan::resepBangunan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaBangunan() << std::endl;
    }
}

void GameConfig(string filePathMisc){
    FileReader fileReader(filePathMisc);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    //vector<string> str_arr = stringToArraySpace(str);

    Pemain::uangWin = std::stoi(fileContentarr[0]);
    Pemain::beratWin = std::stoi(fileContentarr[1]);

    vector<string> str_arr_inv = stringToArraySpace(fileContentarr[2]);
    Pemain::inventoryRowSize = std::stoi(str_arr_inv[0]);
    Pemain::inventoryColumnSize = std::stoi(str_arr_inv[1]);

    vector<string> str_arr_lhn = stringToArraySpace(fileContentarr[3]);
    Petani::lahanRowSize = std::stoi(str_arr_lhn[0]);
    Petani::lahanColumnSize = std::stoi(str_arr_lhn[1]);

    vector<string> str_arr_pet = stringToArraySpace(fileContentarr[4]);
    Peternak::peternakanRowSize = std::stoi(str_arr_pet[0]);
    Peternak::peternakanColumnSize = std::stoi(str_arr_pet[1]);
}

int main() {
    std::string filePathProduk = "produk.txt"; // Replace "input.txt" with your file path
    std::string filePathHewan = "animal.txt";
    std::string filePathTumbuhan = "plant.txt";
    std::string filePathBangunan = "recipe.txt";
    std::string filePathMisc = "misc.txt";

    try {
        std::ifstream fileProduk(filePathProduk);
        if (!fileProduk.is_open()) {
            cout << "File config produk '" << filePathProduk;
            throw FilePathProdukNotFoundException();
        }

        populateConfigProduk(filePathProduk);
        fileProduk.close();

        std::ifstream fileHewan(filePathHewan);
        if (!fileHewan.is_open()) {
            cout << "File config hewan '" << filePathHewan;
            throw FilePathHewanNotFoundException();
        }

        cout << endl;
        populateConfigHewan(filePathHewan);
        fileHewan.close();

        std::ifstream fileTumbuhan(filePathTumbuhan);
        if (!fileTumbuhan.is_open()) {
            cout << "File config tumbuhan '" << filePathTumbuhan;
            throw FilePathTumbuhanNotFoundException();
        }

        cout << endl;
        populateConfigTumbuhan(filePathTumbuhan);
        fileTumbuhan.close();

        std::ifstream fileBangunan(filePathBangunan);
        if (!fileBangunan.is_open()) {
            cout << "File config bangunan '" << filePathBangunan;
            throw FilePathBangunanNotFoundException();
        }

        cout << endl;
        populateConfigBangunan(filePathBangunan);
        fileBangunan.close();

    } catch(UnknownProductTypeException& e){
        cout << e.what() << endl;
    } catch(FilePathProdukNotFoundException& e){
        cout << e.what() << endl;
    } catch(FilePathHewanNotFoundException& e){
        cout << e.what() << endl;
    } catch(FilePathBangunanNotFoundException& e){
        cout << e.what() << endl;
    } catch(const std::exception& e) {
        cerr << e.what() << endl; // Print any error message
        return 1;
    }

    return 0;
}
