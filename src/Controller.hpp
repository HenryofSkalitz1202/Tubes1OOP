#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Pemain.cpp"
using namespace std;

class Controller
{
private:
    std::vector<Pemain*> players;
    size_t current_player_index;
    Pemain* current_player;
    int turn_number;
    bool game_over;

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

    void start_default();
    void start_load();

    bool is_petani(Pemain* player);
    bool is_peternak(Pemain* player);
    bool is_walikota(Pemain* player);

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
    void muat();
    void simpan();
    void tambah_pemain();

};

#endif