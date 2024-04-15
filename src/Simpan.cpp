#include "Simpan.hpp"
#include <sstream>

Simpan::Simpan(string filepath, Controller& controller) : filepath(filepath), controller(controller) {}

void Simpan::write() {
    ofstream SaveFile(this->filepath);
    vector<Pemain*> players = this->controller.getPlayers();
    SaveFile << players.size() << endl;
    for (auto const& player: players) {
        SaveFile << player->getUsername() << " " << player->getStatus() << " " << player->getBeratBadan() << " " << player->getUang() << endl;

        vector<string> inventory = this->inventoryItems(player);
        SaveFile << inventory.size() << endl;

        for (auto const& item: inventory) {
            SaveFile << item << endl;
        }

        if (player->getStatus() == "Petani") {
            vector<string> ladang = this->ladangItems(dynamic_cast<Petani*>(player));
            SaveFile << ladang.size() << endl;
            for (auto const& item: ladang) {
                SaveFile << item << endl;
            }
        } else if (player->getStatus() == "Peternak") {
            vector<string> peternakan = this->peternakanItems(dynamic_cast<Peternak*>(player));
            SaveFile << peternakan.size() << endl;
            for (auto const& item: peternakan) {
                SaveFile << item << endl;
            }
        }
    }
    map<string, int> tokoItems = controller.getListJumlahItemToko();
    SaveFile << tokoItems.size() << endl;
    for (auto const& x: tokoItems) {
        SaveFile << x.first << " " << x.second << endl;
    }
    SaveFile.close();
}

vector<string> Simpan::inventoryItems(Pemain* player) {
    vector<string> itemNames;
    for (size_t i=0; i<Inventory::inventoryRowSize; ++i) {
        for (size_t j=0; j<Inventory::inventoryColumnSize; ++j) {
            if (player->getFromInventory(i, j) != nullptr) {
                itemNames.push_back(player->getFromInventory(i, j)->getNamaAsset());
            }
        }
    }
    return itemNames;
}

vector<string> Simpan::ladangItems(Petani* player) {
    vector<string> items;
    string details;
    for (size_t i=0; i<Ladang::lahanRowSize; ++i) {
        for (size_t j=0; j<Ladang::lahanColumnSize; ++j) {
            string key = player->getLadang().calculateKey(i, j);
            if (player->getFromLadang(key) != nullptr) {
                details = "";
                details += key;
                details += " " + player->getFromLadang(key)->getNamaAsset();
                int umur = this->controller.getTurnNumber() - player->getFromLadang(key)->getTurnInstantiated();
                details += " " + to_string(umur);
                items.push_back(details);
            }
        }
    }
    return items;
}

vector<string> Simpan::peternakanItems (Peternak* player) {
    vector<string> items;
    string details;
    for (size_t i=0; i<Peternakan::peternakanRowSize; ++i) {
        for (size_t j=0; j<Peternakan::peternakanColumnSize; ++j) {
            string key = player->getPeternakan().calculateKey(i, j);
            if (player->getFromPeternakan(key) != nullptr) {
                details = "";
                details += key;
                details += " " + player->getFromPeternakan(key)->getNamaAsset();
                details += " " + to_string(player->getFromPeternakan(key)->getWeight());
                items.push_back(details);
            }
        }
    }
    return items;
}