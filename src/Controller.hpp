#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Pemain.hpp"
using namespace std;

class Controller
{
private:
    std::vector<Pemain*> players;
    size_t current_player_index;
    int turn_number;
    Pemain* current_player;
    bool game_over;

public:
    Controller();
    ~Controller();

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