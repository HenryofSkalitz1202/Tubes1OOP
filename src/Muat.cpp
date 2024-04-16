#include "Muat.hpp"

Muat::Muat(string filepath, Controller& controller) : filepath(filepath), controller(controller) {}

void Muat::read() {
    ifstream file(filepath);

    int num_players;
    file >> num_players;
    file.ignore();

    string line;
    bool walikota_exist = false;

    for (int i = 0; i < num_players; i++) {
        getline(file, line);
        istringstream iss(line);
        string username, type;
        int berat_badan, uang;
        Pemain* player;

        iss >> username >> type >> berat_badan >> uang;

        try {
            if (type == "Petani") {
                player = new Petani(username, berat_badan, uang);
            } else if (type == "Peternak") {
                player = new Peternak(username, berat_badan, uang);
            } else if (type == "Walikota") {
                if (walikota_exist) {
                    throw walikotaAlreadyExistException();
                } else {
                    walikota_exist = true;
                    player = new Walikota(username, berat_badan, uang);
                }
            } else {
                throw playerTypeNotExistException();
            }

        } catch (playerTypeNotExistException& e) {
            cout << e.what() << type << "!" << endl;
            return;
        } catch (walikotaAlreadyExistException& e) {
            cout << e.what();
            return;
        }


        getline(file, line);
        int nInventory = stoi(line);
        for (int j=0; j<nInventory; j++) {
            getline(file, line);
            player->addToInventory(getAsset(line));
        }

        string loc, item;
        int num;
        if (type == "Petani") {
            getline(file, line);
            int nLadang = stoi(line);
            for (int j=0; j<nLadang; j++) {
                getline(file, line);
                istringstream iss(line);
                iss >> loc >> item >> num;
                Tumbuhan* t = Tumbuhan::configTumbuhan[item];
                t->setTurnInstantiated(-1*num);
                dynamic_cast<Petani*>(player)->addToLadang(t, loc);
            }
        } else if (type == "Peternak") {
            getline(file, line);
            int nPeternakan = stoi(line);
            for (int j=0; j<nPeternakan; j++) {
                getline(file, line);
                istringstream iss(line);
                iss >> loc >> item >> num;
                Hewan* h = Hewan::configHewan[item];
                h->setWeight(num);
                dynamic_cast<Peternak*>(player)->addToPeternakan(h, loc);
            }
        }

        this->controller.add_player(player);
    }

    getline(file, line);
    int nItem = stoi(line);
    for (int i=0; i<nItem; i++) {
        getline(file, line);
        istringstream iss(line);
        string item;
        int num;
        iss >> item >> num;
        this->controller.setJumlahItemToko(item, num);
    }
    file.close();
}

Asset* Muat::getAsset(string name) {
    if (Bangunan::resepBangunan.count(name)) {
        return Bangunan::resepBangunan[name];
    } else if (ProductMaterial::configProdukMaterial.count(name)) {
        return ProductMaterial::configProdukMaterial[name];
    } else if (ProductFruit::configProdukFruit.count(name)) {
        return ProductFruit::configProdukFruit[name];
    } else if (ProductHewan::configProdukHewan.count(name)) {
        return ProductHewan::configProdukHewan[name];
    } else if (Hewan::configHewan.count(name)) {
        return Hewan::configHewan[name];
    } else if (Tumbuhan::configTumbuhan.count(name)) {
        return Tumbuhan::configTumbuhan[name];
    }
    return nullptr;
}