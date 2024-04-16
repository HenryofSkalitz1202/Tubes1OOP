#include "Muat.hpp"

Muat::Muat(string filepath, Controller& controller) : filepath(filepath), controller(controller) {}

void Muat::read(){
    ifstream file(filepath);

    cout << "Processing players...." << endl;

    int num_players;
    file >> num_players;
    file.ignore();

    string line;
    bool walikota_exist = false;

    for (int i = 0; i < num_players; i++){
        getline(file, line);
        istringstream iss(line);
        string username, type;
        int berat_badan, uang;
        Pemain* player;

        iss >> username >> type >> berat_badan >> uang;

        if(type == "Petani"){
            player = new Petani(Controller::players.size() + 1, username, uang, berat_badan);
        }else if (type == "Peternak"){
            player = new Peternak(Controller::players.size() + 1, username, uang, berat_badan);
        }else if (type == "Walikota"){
            if(walikota_exist){
                delete player;
                Controller::players.clear();
                file.close();
                throw walikotaAlreadyExistException();
            }else{
                walikota_exist = true;
                player = new Walikota(Controller::players.size() + 1, username, uang, berat_badan);
            }
        }else{
            delete player;
            Controller::players.clear();
            file.close();
            cout << RED << type << NORMAL;
            throw playerTypeNotExistException();
        }

        getline(file, line);
        
        if(!isStringDigit(line) || stoi(line) <= 0){
            delete player;
            Controller::players.clear();
            file.close();
            throw inventorySizeInvalidException();
        }

        int nInventory = stoi(line);

        for (int j = 0; j < nInventory; j++){
            getline(file, line);

            if(getAsset(line) == nullptr){
                delete player;
                Controller::players.clear();
                file.close();
                cout << RED << "An attempt to set item " << line << " to inventory is detected" << NORMAL << endl;
                throw inventoryItemInvalidException();
            }

            player->addToInventory(getAsset(line));
        }

        string loc, item;
        int num;
        if (type == "Petani") {
            getline(file, line);

            if(!isStringDigit(line) || stoi(line) < 0){
                delete player;
                Controller::players.clear();
                file.close();
                throw ladangSizeInvalidException();
            }

            int nLadang = stoi(line);

            for (int j = 0; j < nLadang; j++) {
                getline(file, line);
                istringstream iss(line);
                iss >> loc >> item >> num;

                if(Tumbuhan::configTumbuhan.find(Toko::catalogTumbuhanNama[item]) == Tumbuhan::configTumbuhan.end()){
                    delete player;
                    Controller::players.clear();
                    file.close();
                    cout << RED << item << NORMAL;
                    throw ladangItemInvalidException();
                }

                if(Tumbuhan::configTumbuhan[Toko::catalogTumbuhanNama[item]]->getTumbuhanType() == "MATERIAL_PLANT"){
                    MaterialPlant* t = new MaterialPlant(*dynamic_cast<MaterialPlant*>(Tumbuhan::configTumbuhan[Toko::catalogTumbuhanNama[item]]));
                    t->setTurnInstantiated(-1 * num);
                    dynamic_cast<Petani*>(player)->addToLadang(t, loc);
                }else if(Tumbuhan::configTumbuhan[Toko::catalogTumbuhanNama[item]]->getTumbuhanType() == "FRUIT_PLANT"){
                    FruitPlant* t = new FruitPlant(*dynamic_cast<FruitPlant*>(Tumbuhan::configTumbuhan[Toko::catalogTumbuhanNama[item]]));
                    t->setTurnInstantiated(-1 * num);
                    dynamic_cast<Petani*>(player)->addToLadang(t, loc);
                }
            }
        }else if (type == "Peternak") {
            getline(file, line);

            if(!isStringDigit(line) || stoi(line) < 0){
                delete player;
                Controller::players.clear();
                file.close();
                throw peternakanSizeInvalidException();
            }

            int nPeternakan = stoi(line);
            for (int j = 0; j < nPeternakan; j++) {
                getline(file, line);
                istringstream iss(line);
                iss >> loc >> item >> num;

                if(Hewan::configHewan.find(Toko::catalogHewanNama[item]) == Hewan::configHewan.end()){
                    delete player;
                    Controller::players.clear();
                    file.close();
                    cout << RED << item << NORMAL << endl;
                    throw peternakanItemInvalidException();
                }

                if(Hewan::configHewan[Toko::catalogHewanNama[item]]->getType() == "CARNIVORE"){
                    Carnivore* h = new Carnivore(*dynamic_cast<Carnivore*>(Hewan::configHewan[Toko::catalogHewanNama[item]]));
                    h->setWeight(num);
                    dynamic_cast<Peternak*>(player)->addToPeternakan(h, loc);
                }else if(Hewan::configHewan[Toko::catalogHewanNama[item]]->getType() == "HERBIVORE"){
                    Herbivore* h = new Herbivore(*dynamic_cast<Herbivore*>(Hewan::configHewan[Toko::catalogHewanNama[item]]));
                    h->setWeight(num);
                    dynamic_cast<Peternak*>(player)->addToPeternakan(h, loc);
                }else if(Hewan::configHewan[Toko::catalogHewanNama[item]]->getType() == "OMNIVORE"){
                    Omnivore* h = new Omnivore(*dynamic_cast<Omnivore*>(Hewan::configHewan[Toko::catalogHewanNama[item]]));
                    h->setWeight(num);
                    dynamic_cast<Peternak*>(player)->addToPeternakan(h, loc);
                }
            }
        }

        this->controller.add_player(player);
    }

    cout << GREEN << "Players successfully loaded!\n" << NORMAL << endl;
    cout << "Processing store...." << endl;

    getline(file, line);

    if(!isStringDigit(line) || stoi(line) < 0){
        Controller::players.clear();
        file.close();
        throw storeSizeInvalidException();
    }

    int nItem = stoi(line);
    for (int i = 0; i < nItem; i++) {
        getline(file, line);
        istringstream iss(line);
        string item;
        int num;
        iss >> item >> num;
        if(Bangunan::resepBangunan.find(item) != Bangunan::resepBangunan.end()){
            Toko::catalogBangunan[item] = num;
        }else if(ProductMaterial::configProdukMaterial.find(item) != ProductMaterial::configProdukMaterial.end()){
            Toko::catalogProduk[item] = num;
        }else if(ProductFruit::configProdukFruit.find(Toko::catalogProdukFruitNama[item]) != ProductFruit::configProdukFruit.end()){
            Toko::catalogProduk[Toko::catalogProdukFruitNama[item]] = num;
        }else if(ProductHewan::configProdukHewan.find(Toko::catalogProdukHewanNama[item]) != ProductHewan::configProdukHewan.end()){
            Toko::catalogProduk[Toko::catalogProdukHewanNama[item]] = num;
        }else{
            for(const auto& pair : Toko::catalogBangunan){
                Toko::catalogBangunan[pair.first] = 0;
            }

            for(const auto& pair : Toko::catalogProduk){
                Toko::catalogProduk[pair.first] = 0;
            }
            
            Controller::players.clear();
            file.close();
            cout << RED << item << NORMAL;
            throw UnknownProductException();
        }
    }

    file.close();
}

Asset* Muat::getAsset(string name) {
    if (Bangunan::resepBangunan.count(name)) {
        return Bangunan::resepBangunan[name];
    } else if (ProductMaterial::configProdukMaterial.count(name)) {
        return ProductMaterial::configProdukMaterial[name];
    } else if (ProductFruit::configProdukFruit.count(Toko::catalogProdukFruitNama[name])) {
        return ProductFruit::configProdukFruit[Toko::catalogProdukFruitNama[name]];
    } else if (ProductHewan::configProdukHewan.count(Toko::catalogProdukHewanNama[name])) {
        return ProductHewan::configProdukHewan[Toko::catalogProdukHewanNama[name]];
    } else if (Hewan::configHewan.count(Toko::catalogHewanNama[name])) {
        return Hewan::configHewan[Toko::catalogHewanNama[name]];
    } else if (Tumbuhan::configTumbuhan.count(Toko::catalogTumbuhanNama[name])) {
        return Tumbuhan::configTumbuhan[Toko::catalogTumbuhanNama[name]];
    }
    return nullptr;
}

bool Muat::isStringDigit(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;  // If any character is not a digit, return false
        }
    }
    return true;  // All characters are digits
}