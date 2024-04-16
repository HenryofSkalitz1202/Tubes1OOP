#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "Exception.hpp"
#include "input.cpp"
#include "Pemain.hpp"
#include "Hewan/Hewan.hpp"
#include "Hewan/Carnivore.hpp"
#include "Hewan/Herbivore.hpp"
#include "Hewan/Omnivore.hpp"
#include "Tumbuhan.hpp"
#include "Toko.hpp"
#include "Grid.hpp"

using namespace std;

class Import;

class Controller
{
private:
    vector<Pemain*> players;
    size_t current_player_index;
    Pemain* current_player;
    int turn_number;
    bool game_over;
    Toko toko;

public:
    Controller();
    ~Controller();

    static vector<string> stringToArrayEnter(const string& input);
    static vector<string> stringToArraySpace(const string& input);
    static void printVector(const vector<string>& vec);
    static void populateConfigProduk(string filePathProduk);
    static void populateConfigHewan(string filePathHewan);
    static void populateConfigTumbuhan(string filePathTumbuhan);
    static void populateConfigBangunan(string filePathBangunan);
    static void GameConfig(string filePathMisc);

    void set_current_player(Pemain* player);
    Pemain* get_current_player();
    void print_current_player();

    void sort_players();
    void add_player(Pemain* player);
    Pemain* get_first_player();
    void print_players();

    bool is_game_over();
    void is_won();

    void start_option();
    void start_default();

    bool is_petani(Pemain* player);
    bool is_peternak(Pemain* player);
    bool is_walikota(Pemain* player);

    vector<Pemain*> getPlayers();
    map<string, int> getListJumlahItemToko();
    void setJumlahItemToko(string itemName, int jumlah);
    int getTurnNumber();

    void readCommand();
    void next();
    void cetak_penyimpanan();
    void pungut_pajak();
    void cetak_ladang();
    void cetak_peternakan();
    void tanam();
    void ternak();
    void bangun();
    void makan();
    void kasih_makan();
    void beli();
    void jual();
    void panen();
    void muat(string filePathState);
    void simpan();
    void tambah_pemain();
};

#endif