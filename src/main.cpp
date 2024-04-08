#include "Pemain.hpp"
#include "input.cpp"
#include "Exception.hpp"
#include "Produk.cpp"
#include <iostream>
#include <vector>
#include <sstream>

int Pemain::beratWin = 50;
int Pemain::uangWin = 40;
int Pemain::defaultBerat = 69;
int Pemain::defaultUang = 100;

int countEnters(const string text) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            count++;
        }
    }
    return count;
}

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

int main() {
    std::string filePathProduk = "produk.txt"; // Replace "input.txt" with your file path
    FileReader fileReader(filePathProduk);
    try {
        std::string fileContent = fileReader.readText();
        //std::cout << fileContent << std::endl; // Print the file content
        //int number_of_lines = countEnters(fileContent) + 1;

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
    } catch(UnknownProductTypeException& e){
        cout << e.what() << endl;
    }  catch (const std::exception& e) {
        cerr << e.what() << endl; // Print any error message
        return 1;
    }

    return 0;
}
