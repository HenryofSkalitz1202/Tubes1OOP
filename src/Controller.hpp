#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Pemain.cpp"
using namespace std;

class Import;

class Controller
{
private:
    //std::vector<Pemain*> players;
    int current_player_index;
    Pemain* current_player;
    int turn_number;
    bool game_over;
    Toko store;

public:
    static vector<Pemain*> players;
    Controller();
    ~Controller();

    static vector<string> stringToArrayEnter(const string& input);
    static vector<string> stringToArraySpace(const string& input);
    static vector<string> stringToArrayDot(const string& input);
    static int custom_stoi(const std::string& str);
    static void printMap(const std::map<std::string, int>& myMap);
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

    vector<Pemain*> getPlayers();
    int getTurnNumber();

    Toko getToko();
    map<string, int> getRekapToko();

    bool is_game_over();
    void is_won();

    //void start_default();
    //void start_load();

    bool is_petani(Pemain* player);
    bool is_peternak(Pemain* player);
    bool is_walikota(Pemain* player);

    bool isValidCommand(string command, Pemain* player);
    void readCommand(Pemain* player);
    void next();
    void cetak_penyimpanan(Pemain* player);
    void pungut_pajak(Walikota* walikota);
    void cetak_ladang(Petani* petani);
    void cetak_peternakan(Peternak* peternak);
    void tanam(Petani* petani);
    void ternak(Peternak* peternak);
    void bangun(Walikota* walikota);
    void makan(Pemain* player);
    void kasih_makan(Peternak* peternak);
    void beli(Pemain* player);
    void jual(Pemain* player);
    void panen(Petani* petani);
    void panen(Peternak* peternak);
    void tambah_pemain(Walikota* walikota);
    void muat(string filePathState);
    void simpan();
};

#endif