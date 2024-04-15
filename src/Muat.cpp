#include "Muat.hpp"
#include "Controller.hpp"

Muat::Muat(string filepath, Controller& controller) : filepath(filepath), controller(controller) {}

void Muat::read() {
    ifstream file(filepath);

    int num_players;
    file >> num_players;
    file.ignore();

    for (int i = 0; i < num_players; i++) {
        string line;
        getline(file, line);
        istringstream iss(line);
        string username, type;
        int berat_badan, uang;

        iss >> username >> type >> berat_badan >> uang;

        if (type == "Petani") {
            Petani* petani = new Petani(username, berat_badan, uang);
            controller.add_player(petani);
        } else if (type == "Peternak") {
            Peternak* peternak = new Peternak(username, berat_badan, uang);
            controller.add_player(peternak);
        } else if (type == "Walikota") {
            Walikota* walikota = new Walikota(username, berat_badan, uang);
            controller.add_player(walikota);
        }

    }
}