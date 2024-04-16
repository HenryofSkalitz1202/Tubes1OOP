#include "Simpan.hpp"
#include <sstream>
#include <iomanip>
#include <fstream>

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

        if (dynamic_cast<Petani*>(player)) {
            vector<string> ladang = this->ladangItems(dynamic_cast<Petani*>(player));
            SaveFile << ladang.size() << endl;
            for (auto const& item: ladang) {
                SaveFile << item << endl;
            }
        } else if (dynamic_cast<Peternak*>(player)) {
            vector<string> peternakan = this->peternakanItems(dynamic_cast<Peternak*>(player));
            SaveFile << peternakan.size() << endl;
            for (auto const& item: peternakan) {
                SaveFile << item << endl;
            }
        }
    }

    map<string, int> tokoItems = this->controller.getRekapToko();
    SaveFile << tokoItems.size() << endl;
    for (auto const& x: tokoItems) {
        SaveFile << x.first << " " << x.second << endl;
    }
    SaveFile.close();
}

vector<string> Simpan::inventoryItems(Pemain* player) {
    vector<string> itemNames;
    for (size_t i = 0; i < Inventory::inventoryRowSize; ++i) {
        for (size_t j = 0; j < Inventory::inventoryColumnSize; ++j) {
            if (player->getFromInventory(calculateKey(i, j)) != nullptr) {
                itemNames.push_back(player->getFromInventory(calculateKey(i, j))->getNamaAsset());
            }
        }
    }
    return itemNames;
}

vector<string> Simpan::ladangItems(Petani* player) {
    vector<string> items;
    string details;
    for (size_t i = 0; i < Ladang::lahanRowSize; ++i) {
        for (size_t j = 0; j < Ladang::lahanColumnSize; ++j) {
            string key = calculateKey(i, j);
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
    for (size_t i = 0; i < Peternakan::peternakanRowSize; i++) {
        for (size_t j = 0; j < Peternakan::peternakanColumnSize; j++) {
            string key = calculateKey(i, j);
            if (player->getFromPeternakan(key) != nullptr) {
                string details = "";
                details += key;
                details += " " + player->getFromPeternakan(key)->getNamaAsset();
                details += " " + to_string(player->getFromPeternakan(key)->getWeight());
                items.push_back(details);
            }
        }
    }
    return items;
}

string Simpan::calculateKey(size_t row, size_t col) {
    std::ostringstream oss;
    char key_alphabet = 'A' + col;
    oss << std::setw(2) << std::setfill('0') << row + 1;
    std::string final_key = key_alphabet + oss.str();

    oss.str("");
    oss.clear();

    return final_key;
}