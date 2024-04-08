#include "Pemain.hpp"
#include "input.cpp"
#include "Exception.hpp"
#include "Produk.cpp"
#include "Hewan.cpp"
#include "Tumbuhan.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>

int Pemain::beratWin = 50;
int Pemain::uangWin = 40;
int Pemain::defaultBerat = 69;
int Pemain::defaultUang = 100;

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
    map<string, Produk*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Produk* produkPtr = nullptr;
        if(str_arr[3] == "PRODUCT_MATERIAL_PLANT"){
            produkPtr = new ProductMaterial(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
        }else if(str_arr[3] == "PRODUCT_FRUIT_PLANT"){
            produkPtr = new ProductFruit(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
        }else if(str_arr[3] == "PRODUCT_ANIMAL"){
            produkPtr = new ProductHewan(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownProductTypeException();
        }
        mp.insert({str_arr[1], produkPtr});
    }

    Produk::configProduk.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Produk::configProduk.insert({pair.first, pair.second});
    }

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Produk::configProduk) {
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
            tumbuhanPtr = new MaterialPlant(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]), std::stoi(str_arr[6]));
        }else if(str_arr[3] == "FRUIT_PLANT"){
            tumbuhanPtr = new FruitPlant(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]), std::stoi(str_arr[6]));
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

int main() {
    std::string filePathProduk = "produk.txt"; // Replace "input.txt" with your file path
    std::string filePathHewan = "animal.txt";
    std::string filePathTumbuhan = "plant.txt";

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

        populateConfigHewan(filePathHewan);
        fileHewan.close();

        std::ifstream fileTumbuhan(filePathTumbuhan);
        if (!fileTumbuhan.is_open()) {
            cout << "File config hewan '" << filePathTumbuhan;
            throw FilePathTumbuhanNotFoundException();
        }

        populateConfigTumbuhan(filePathTumbuhan);
        fileTumbuhan.close();
    } catch(UnknownProductTypeException& e){
        cout << e.what() << endl;
    } catch(FilePathProdukNotFoundException& e){
        cout << e.what() << endl;
    } catch(FilePathHewanNotFoundException& e){
        cout << e.what() << endl;
    } catch(const std::exception& e) {
        cerr << e.what() << endl; // Print any error message
        return 1;
    }

    return 0;
}
