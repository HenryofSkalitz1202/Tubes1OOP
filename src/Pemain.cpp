#include "Pemain.hpp"
#include <iostream>

using namespace std;

int Pemain::uangWin;
int Pemain::beratWin;
//<---------------PEMAIN----------------->
Pemain::~Pemain(){
}

void Pemain::setUsername(string username){
    this->username = username;
}

void Pemain::setUang(int uang){
    this->uang = uang;
}

void Pemain::setberatBadan(int beratBadan){
    this->beratBadan = beratBadan;
}

void Pemain::addToInventory(Asset* item){
    this->inventory.addItem(item);
}

string Pemain::getUsername(){
    return this->username;
}

int Pemain::getUang(){
    return this->uang;
}

int Pemain::getBeratBadan(){
    return this->beratBadan;
}

Asset* Pemain::getFromInventory(string key){
    return this->inventory.get(key);
}

Inventory Pemain::getInventory(){
    Inventory inv;
    inv = this->inventory;
    return inv;
}

void Pemain::printInventory(){
    this->inventory.print();
}

void Pemain::jualAsset(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        std::cout << "Berikut merupakan penyimpanan Anda" << std::endl;
        this->inventory.print();

        bool invalidPetakFound = true;
        vector<string> petakJual;
        string petakJualInput;
        while (invalidPetakFound) {
            invalidPetakFound = false;

            petakJualInput = "";
            std::cout << "\nSilahkan pilih petak yang ingin Anda jual!\nPetak : " << std::endl;
            cin >> petakJualInput;
            petakJual = Pemain::stringToArrayComma(petakJualInput);

            for (const std::string& petak : petakJual) {
                if (!this->inventory.isValidKey(petak)) {
                    invalidPetakFound = true;
                    std::cout << petak << " is invalid" << std::endl;
                }else if(this->inventory.get(petak) == nullptr){
                    invalidPetakFound = true;
                    std::cout << petak << " is empty" << std::endl;
                }
            }
        }

        for(const string& petak : petakJual){
            Asset* assetptr = this->inventory.get(petak);
            if(dynamic_cast<Hewan*>(assetptr) || dynamic_cast<Tumbuhan*>(assetptr)){
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<Bangunan*>(assetptr)){
                Toko::catalogBangunan[assetptr->getNamaAsset()]++;
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<ProductMaterial*>(assetptr)){
                Toko::catalogProduk[assetptr->getNamaAsset()]++;
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<ProductFruit*>(assetptr) || dynamic_cast<ProductHewan*>(assetptr)){
                Toko::catalogProduk[assetptr->getKodeHuruf()]++;
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }
        }
    }catch(inventoryEmptyException& e){
        std::cout << e.what();
    }
}

void Pemain::makan(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();

        if((this->inventory.getJumlahProductFruit() + this->inventory.getJumlahProductHewan()) == 0){
            throw noFoodException();
        }

        std::cout << "Pilih makanan dari penyimpanan" << std::endl;

        string slot;
        bool validInv = false;
        while(!validInv){
            std::cout << "Slot: ";
            std::cin >> slot;

            if(!this->inventory.isValidKey(slot)){
                std::cout << slot << " is invalid" << std::endl;
            }else if(this->getFromInventory(slot) == nullptr){
                std::cout << slot << " is empty" << std::endl;
            }else if(!dynamic_cast<ProductFruit*>(this->getFromInventory(slot)) && !dynamic_cast<ProductHewan*>(this->getFromInventory(slot))){
                std::cout << this->getFromInventory(slot)->getNamaAsset() << " is inedible" << std::endl;
            }else{
                validInv = true;
            }
        }

        Produk* makanan = dynamic_cast<Produk*>(this->inventory.get(slot));
        this->setberatBadan(this->getBeratBadan() + makanan->getAddedWeight());
        this->inventory.setNull(slot);

        std::cout << "Dengan lahapnya, kamu memakan hidangan itu..." << std::endl;
        std::cout << "Alhasil, berat badan kamu naik menjadi " << this->getBeratBadan();
    }catch(inventoryEmptyException& e){
        std::cout << e.what();
    }catch(noFoodException& e){
        std::cout << e.what();
    }
}

//<---------------PETANI----------------->
Petani::Petani(int petaniID, string username){
    this->petaniID = petaniID;
    this->username = username;
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
}

Petani::Petani(int petaniID, string username, int uang, int beratBadan, Inventory inventory, Ladang ladang){
    this->petaniID = petaniID;
    this->username = username;
    this->uang = uang;
    this->beratBadan = beratBadan;
    this->inventory = inventory;
    this->ladang = ladang;
}

Petani::~Petani(){
    //delete[] ladang;
    //~Pemain();
}

Petani::Petani(Petani& other){
    this->petaniID = other.getPetaniID();
    this->username = other.getUsername();
    this->uang = other.getUang();
    this->beratBadan = other.getBeratBadan();
    this->inventory = other.getInventory();
    this->ladang = other.getLadang();
}

Petani& Petani::operator=(const Petani& other){
    this->petaniID = other.petaniID;
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->inventory = other.inventory;
    this->ladang = other.ladang;
}

void Petani::setPetaniID(int petaniID){
    this->petaniID = petaniID;
}

int Petani::getPetaniID(){
    return this->petaniID;
}

Ladang Petani::getLadang(){
    return this->ladang;
}

void Petani::tanamTanaman(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();
        cout << "tumbuhan: " << this->inventory.getJumlahTumbuhan() << endl;

        if(this->inventory.getJumlahTumbuhan() <= 0){
            throw noTumbuhanAvailableException();
        }

        if(this->ladang.isFull()){
            throw ladangFullException();
        }

        std::cout << "Pilih tanaman dari penyimpanan" << std::endl;
        this->inventory.print();
        
        string key_inv;
        bool validInv = false;
        while(!validInv){
            std::cout << "Slot : ";
            std::cin >> key_inv;

            if(!this->inventory.isValidKey(key_inv)){
                std::cout << key_inv << " is invalid" << std::endl;
            }else if(this->getFromInventory(key_inv) == nullptr){
                std::cout << key_inv << " is empty" << std::endl;
            }else if(!dynamic_cast<Tumbuhan*>(this->getFromInventory(key_inv))){
                std::cout << "Object in " << key_inv << " is not of Tumbuhan type" << std::endl;
            }else{
                validInv = true;
            }
        }

        Tumbuhan* tumbuhan = dynamic_cast<Tumbuhan*>(this->getFromInventory(key_inv));  

        std::cout << "Kamu memilih " << tumbuhan->getNamaAsset() << std::endl;
        std::cout << "\nPilih petak yang akan ditanami" << std::endl;
        this->ladang.print();

        string key_ladang;
        bool validLad = false;
        while(!validLad){
            std::cout << "Petak tanah: ";
            std::cin >> key_ladang;

            if(!this->inventory.isValidKey(key_ladang)){
                std::cout << key_ladang << " is invalid" << std::endl;
            }else if(this->ladang.get(key_ladang) != nullptr){
                std::cout << key_ladang << " is not vacant" << std::endl;
            }else{
                validLad = true;
            }
        }

        this->ladang.setWithKey(key_ladang, tumbuhan);
        this->inventory.setNull(key_inv);

        std::cout << "\nCangkul, cangkul, cangkul yang dalam~!" << std::endl;
        std::cout << tumbuhan->getNamaAsset() << " berhasil ditanam!";
    }catch(inventoryEmptyException& e){
        std::cout << e.what();
    }catch(noTumbuhanAvailableException& e){
        std::cout << e.what();
    }catch(ladangFullException& e){
        std::cout << e.what();
    }
}

void Petani::panenTanaman(){
    try{
        if(this->ladang.isEmpty()){
            throw ladangEmptyException();
        }

        if(!this->ladang.isAvailablePanen()){
            throw noneSiapPanenLadangException();
        }

        if(!this->inventory.isFull()){
            throw inventoryFullException();
        }

        this->ladang.print();

        map<string, int> rekapLadang = this->ladang.rekapLadang();
        for(const auto& pair : rekapLadang){
            std::cout << "- " << pair.first << ": " << Tumbuhan::configTumbuhan[pair.first]->getNamaAsset() << std::endl;
        }

        std::cout << "\nPilih tanaman siap panen yang kamu miliki" << std::endl;
        int idx = 0;
        map<int, string> mapIdxKode;
        for(const auto& pair : rekapLadang){
            if(pair.second > 0){
                std::cout << ++idx << ". " << pair.first << " (" << pair.second << " petak siap panen)" << std::endl;
                mapIdxKode.insert({idx, pair.first});
            }
        }

        int nomor_tanaman;
        bool validNomorTanaman = false;
        while(!validNomorTanaman){
            nomor_tanaman = 0;
            std::cout << "Nomor tanaman yang ingin dipanen: ";
            std::cin >> nomor_tanaman;

            if(mapIdxKode.find(nomor_tanaman) == mapIdxKode.end()){
                std::cout << "Nomor tanaman is invalid!\n" << std::endl;
            }else{
                validNomorTanaman = true;
            }
        }

        int jumlah_petak;
        bool validJumlahPetak = false;

        while(!validJumlahPetak){
            jumlah_petak = 0;
            std::cout << "\nJumlah petak yang ingin dipanen: ";
            std::cin >> jumlah_petak;

            if(jumlah_petak <= 0){
                std::cout << "Jumlah petak is invalid!\n";
            }else if(jumlah_petak > rekapLadang[mapIdxKode[nomor_tanaman]]){
                std::cout << "You are trying to harvest more than the amount of petak that is currently available to harvest!\n";
            }else if(this->inventory.countAvailableCapacity() < jumlah_petak){
                std::cout << "Available inventory capacity is not enough!\n";
            }else{
                validJumlahPetak = true;
            }
        }

        std::cout << "\nPilih petak yang ingin dipanen:" << std::endl;
        string str_key = "";
        vector<string> key_vec;

        for(int i = 1; i <= jumlah_petak; i++){
            string temp_key;
            bool validTempKey = false;
            while(!validTempKey){
                temp_key = "";

                std::cout << "Petak ke-" << i << ": ";
                std::cin >> temp_key;

                if(!this->ladang.isValidKey(temp_key)){
                    std::cout << temp_key << " is invalid" << std::endl;
                }else if(this->ladang.get(temp_key) == nullptr){
                    std::cout << temp_key << " is empty" << std::endl;
                }else if(this->ladang.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_tanaman]){
                    std::cout << temp_key << " doesn't contain " << mapIdxKode[nomor_tanaman] << "." << std::endl;
                }else{
                    key_vec.push_back(temp_key);
                    validTempKey = true;
                }
            }

            if(i == 1){
                str_key += temp_key;
            }else{
                str_key = str_key + ", " + temp_key;
            }
        }

        for(string key : key_vec){
            this->inventory.addItem(this->ladang.get(key));
            this->ladang.setNull(key);
        }

        std::cout << jumlah_petak << " petak tanaman " << mapIdxKode[nomor_tanaman] << " pada petak " << str_key << " telah dipanen." << std::endl;
    }catch(ladangEmptyException& e){
        std::cout << e.what();
    }catch(noneSiapPanenLadangException& e){
        std::cout << e.what();
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

void Petani::beliAsset(Toko* store){
    try{
        if(store->findCheapest() > this->uang){
            throw uangInsufficientException();
        }

        if(this->inventory.isFull()){
            throw inventoryFullException();
        }

        std::cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda beli" << endl;
        int idx = 0;
        map<int, string> mapIdxKode;
        map<string, string> mapType;
        for(const auto& pair : Toko::catalogBangunan){
            if(pair.second > 0){
                std::cout << ++idx << ". " << pair.first << " - " << Bangunan::resepBangunan[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                mapIdxKode.insert({idx, pair.first});
                mapType.insert({pair.first, Bangunan::resepBangunan[pair.first]->getAssetType()});
            }
        }

        for(const auto& pair : Toko::catalogProduk){
            if(ProductMaterial::configProdukMaterial.find(pair.first) != ProductMaterial::configProdukMaterial.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << pair.first << " - " << ProductMaterial::configProdukMaterial[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductMaterial::configProdukMaterial[pair.first]->getProdukType()});
                }
            }else if(ProductFruit::configProdukFruit.find(pair.first) != ProductFruit::configProdukFruit.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << ProductFruit::configProdukFruit[pair.first]->getNamaAsset() << " - " << ProductFruit::configProdukFruit[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductFruit::configProdukFruit[pair.first]->getProdukType()});
                }
            }else if(ProductHewan::configProdukHewan.find(pair.first) != ProductHewan::configProdukHewan.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << ProductHewan::configProdukHewan[pair.first]->getNamaAsset() << " - " << ProductHewan::configProdukHewan[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductHewan::configProdukHewan[pair.first]->getProdukType()});
                }
            }
        }

        for(string hewan : Toko::catalogHewan){
            std::cout << ++idx << ". " << Hewan::configHewan[hewan]->getNamaAsset() << " - " << Hewan::configHewan[hewan]->getPrice() << std::endl;
            mapIdxKode.insert({idx, hewan});
            mapType.insert({hewan, Hewan::configHewan[hewan]->getAssetType()});
        }

        for(string tumbuhan : Toko::catalogTumbuhan){
            std::cout << ++idx << ". " << Tumbuhan::configTumbuhan[tumbuhan]->getNamaAsset() << " - " << Tumbuhan::configTumbuhan[tumbuhan]->getPrice() << std::endl;
            mapIdxKode.insert({idx, tumbuhan});
            mapType.insert({tumbuhan, Tumbuhan::configTumbuhan[tumbuhan]->getAssetType()});
        }

        std::cout << "Uang Anda: " << this->getUang() << std::endl;
        std::cout << "Slot penyimpanan tersedia: " << this->inventory.countAvailableCapacity() << std::endl;

        int nomorBarang;
        bool validNomorBarang = false;
        while(!validNomorBarang){
            nomorBarang = 0;
            std::cout << "Barang ingin dibeli: ";
            cin >> nomorBarang;

            if(mapIdxKode.find(nomorBarang) == mapIdxKode.end()){
                std::cout << YELLOW << "Nomor barang is invalid!" << NORMAL << std::endl;
            }else if(Toko::catalogPrice[mapIdxKode[nomorBarang]] > this->uang){
                std::cout << YELLOW << "Barang is too expensive!" << std::endl;
            }else{
                validNomorBarang = true;
            }
        }

        int kuantitas;
        Asset* barang;
        bool validKuantitas = false;
        bool kuantitasCukup = false;
        while(!validKuantitas){
            kuantitas = 0;
            barang = nullptr;
            std::cout << "Kuantitas: ";
            cin >> kuantitas;

            if(kuantitas <= 0){
                std::cout << YELLOW << "Kuantitas is invalid!" << NORMAL << std::endl;
            }else{
                if(mapType[mapIdxKode[nomorBarang]] == "BANGUNAN"){
                    if(kuantitas > Toko::catalogBangunan[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!" << NORMAL << std::endl;
                    }else{
                        barang = Bangunan::resepBangunan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_MATERIAL_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!" << NORMAL << std::endl;
                    }else{
                        barang = ProductMaterial::configProdukMaterial[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_FRUIT_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]]->getNamaAsset() << "!" << NORMAL << std::endl;
                    }else{
                        barang = ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_HEWAN"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]]->getNamaAsset() << "!" << NORMAL << std::endl;
                    }else{
                        barang = ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "HEWAN"){
                    barang = Hewan::configHewan[mapIdxKode[nomorBarang]];
                    kuantitasCukup = true;
                }else if(mapType[mapIdxKode[nomorBarang]] == "TUMBUHAN"){
                    barang = Tumbuhan::configTumbuhan[mapIdxKode[nomorBarang]];
                    kuantitasCukup = true;
                }else{
                    cout << "bocor sini" << endl;
                }
            }

            cout << "Kuantitas cukup " << kuantitasCukup << endl; 
            if(kuantitasCukup){
                if(this->uang >= kuantitas * Toko::catalogPrice[mapIdxKode[nomorBarang]]){
                    std::cout << GREEN << "Selamat! Anda berhasil membeli " << kuantitas << barang->getNamaAsset() << NORMAL << std::endl;
                    validKuantitas = true;
                }else{
                    std::cout << YELLOW << "You don't have enough money to buy that much!" << NORMAL << std::endl;
                }
            }else{
                cout << "bocor di dieu" << endl;
            }
        }

        std::cout << "\nPilih slot untuk menyimpan barang yang Anda beli!" << std::endl;
        this->inventory.print();

        bool invalidPetakFound = true;
        vector<string> petakBeli;
        string petakBeliInput;
        while (invalidPetakFound){
            invalidPetakFound = false;

            petakBeliInput = "";
            std::cout << "Petak slot : ";
            cin >> petakBeliInput;
            petakBeli = Pemain::stringToArrayComma(petakBeliInput);

            for (const std::string& petak : petakBeli) {
                if (!this->inventory.isValidKey(petak)) {
                    invalidPetakFound = true;
                    std::cout << YELLOW << petak << " is invalid" << NORMAL << std::endl;
                }else if(this->inventory.get(petak) != nullptr){
                    invalidPetakFound = true;
                    std::cout << YELLOW << petak << " is not available" << NORMAL << std::endl;
                }
            }
        }

        for(const string& petak : petakBeli){
            cout << "petak: " << petak << endl;
            cout << "length: " << petakBeli.size() << endl;
            cout << "barang: " << barang->getKodeHuruf() << " " << barang->getNamaAsset() << endl;
            this->inventory.setWithKey(petak, barang);
            this->uang -= barang->getPrice();
            if(dynamic_cast<Bangunan*>(barang)){
                Toko::catalogBangunan[barang->getNamaAsset()]--;
            }else if(dynamic_cast<ProductMaterial*>(barang)){
                Toko::catalogProduk[barang->getNamaAsset()]--;
            }else if(dynamic_cast<ProductFruit*>(barang) || dynamic_cast<ProductHewan*>(barang)){
                Toko::catalogProduk[barang->getKodeHuruf()]--;
            }
        }

        std::cout << GREEN << barang->getNamaAsset() << " berhasil disimpan dalam penyimpanan!" << NORMAL << std::endl;
    }catch(uangInsufficientException& e){
        std::cout << e.what();
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

int Petani::getNetWorth(){
    return this->inventory.getTotalWorth() + this->ladang.getTotalWorth() + this->uang;
}

int Petani::countPajak(){
    int kkp = this->getNetWorth() - this->ktkp;
    if(kkp <= 0){
        return 0;
    }else if(kkp <= 6){
        return 0.05 * kkp;
    }else if(kkp <= 25){
        return 0.15 * kkp;
    }else if(kkp <= 50){
        return 0.25 * kkp;
    }else if(kkp <= 500){
        return 0.3 * kkp;
    }else{
        return 0.35 * kkp;
    }
}

//<---------------WALIKOTA----------------->
Walikota::Walikota(int walikotaID, string username){
    this->walikotaID = walikotaID;
    this->username = username;
    this->uang = Pemain::defaultUang;
    this->beratBadan = Pemain::defaultBerat;
}

Walikota::Walikota(int walikotaID, string username, int uang, int beratBadan, Inventory inventory){
    this->walikotaID = walikotaID;
    this->username = username;
    this->uang = uang;
    this->beratBadan = beratBadan;
    this->inventory = inventory;
}

Walikota::~Walikota(){
    //~Pemain();
}

Walikota::Walikota(Walikota& other){
    this->walikotaID = other.getWalikotaID();
    this->username = other.getUsername();
    this->uang = other.getUang();
    this->beratBadan = other.getBeratBadan();
    this->inventory = other.getInventory();
}
  
Walikota& Walikota::operator=(const Walikota& other){
    this->walikotaID = other.walikotaID;
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->inventory = other.inventory;
}

void Walikota::setWalikotaID(int walikotaID){
    this->walikotaID = walikotaID;
}

int Walikota::getWalikotaID(){
    return this->walikotaID;
}
  
void Walikota::bangunBangunan(){
    Bangunan::printResep();
    map<string, int> myMaterial = this->inventory.rekapMaterial();
    bool found = false;
    string namaBangunan = "";

    if(this->inventory.isFull()){
        throw inventoryFullException();
    }

    while(!found){
        std::cout << "\nBangunan yang ingin dibangun: ";
        cin >> namaBangunan;

        if(Bangunan::resepBangunan.find(namaBangunan) == Bangunan::resepBangunan.end()){
            std::cout << "Kamu tidak punya resep bangunan tersebut!" << std::endl;
        }else{
            found = true;
        }
    }

    map<string, int> materialKurang;
    bool uangCukup = true;
    bool materialCukup = true;

    if(this->uang < Bangunan::resepBangunan[namaBangunan]->getPrice()){
        materialKurang.insert({"gulden", Bangunan::resepBangunan[namaBangunan]->getPrice() - this->uang});
        uangCukup = false;
    }

    for(const auto& pair : Bangunan::resepBangunan[namaBangunan]->getListBahan()){
        if(myMaterial[pair.first] < pair.second){
            materialCukup = false;
            materialKurang.insert({pair.first, pair.second - myMaterial[pair.first]});
        }
    }

    if(materialCukup && uangCukup){
        Bangunan* new_building = Bangunan::resepBangunan[namaBangunan];

        this->uang -= new_building->getPrice();

        for(const auto& pair : myMaterial){
            for(int i = 0; i < pair.second; i++){
                this->inventory.findAndRemoveItem(pair.first);
            }
        }

        this->inventory.addItem(new_building);
        std::cout << new_building->getNamaAsset() << " berhasil dibangun dan telah menjadi hak milik walikota!";
    }else{
        std::cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
        bool first = true;
        for (const auto& pair : materialKurang) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << pair.second << " " << pair.first;
            first = false;
        }
        std::cout << std::endl;
    }
}

void Walikota::tambahAkun(vector<Pemain*> players){
    if(this->uang < 50){
        throw uangInsufficientException();
    }  

    string jenis_pemain;
    std::cout << "Masukkan jenis pemain: ";
    cin >> jenis_pemain;

    string nama_pemain;
    std::cout << "Masukkan nama pemain: ";
    cin >> nama_pemain;

    std::cout << "Pemain baru ditambahkan!\nSelamat datang \"" << nama_pemain << "\" di kota ini!" << std::endl;
}

void Walikota::beliAsset(Toko* store){
    try{
        if(store->findCheapest() > this->uang){
            throw uangInsufficientException();
        }

        if(this->inventory.isFull()){
            throw inventoryFullException();
        }

        std::cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda beli" << endl;
        int idx = 0;
        map<int, string> mapIdxKode;
        map<string, string> mapType;
        for(const auto& pair : Toko::catalogProduk){
            if(ProductMaterial::configProdukMaterial.find(pair.first) != ProductMaterial::configProdukMaterial.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << pair.first << " - " << ProductMaterial::configProdukMaterial[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductMaterial::configProdukMaterial[pair.first]->getProdukType()});
                }
            }else if(ProductFruit::configProdukFruit.find(pair.first) != ProductFruit::configProdukFruit.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << ProductFruit::configProdukFruit[pair.first]->getNamaAsset() << " - " << ProductFruit::configProdukFruit[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductFruit::configProdukFruit[pair.first]->getProdukType()});
                }
            }else if(ProductHewan::configProdukHewan.find(pair.first) != ProductHewan::configProdukHewan.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << ProductHewan::configProdukHewan[pair.first]->getNamaAsset() << " - " << ProductHewan::configProdukHewan[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductHewan::configProdukHewan[pair.first]->getProdukType()});
                }
            }
        }

        for(string hewan : Toko::catalogHewan){
            std::cout << ++idx << ". " << Hewan::configHewan[hewan]->getNamaAsset() << " - " << Hewan::configHewan[hewan]->getPrice() << std::endl;
            mapIdxKode.insert({idx, hewan});
            mapType.insert({hewan, Hewan::configHewan[hewan]->getAssetType()});
        }

        for(string tumbuhan : Toko::catalogTumbuhan){
            std::cout << ++idx << ". " << Tumbuhan::configTumbuhan[tumbuhan]->getNamaAsset() << " - " << Tumbuhan::configTumbuhan[tumbuhan]->getPrice() << std::endl;
            mapIdxKode.insert({idx, tumbuhan});
            mapType.insert({tumbuhan, Tumbuhan::configTumbuhan[tumbuhan]->getAssetType()});
        }

        std::cout << "Uang Anda: " << this->getUang() << std::endl;
        std::cout << "Slot penyimpanan tersedia: " << this->inventory.countAvailableCapacity() << std::endl;

        int nomorBarang;
        bool validNomorBarang = false;
        while(!validNomorBarang){
            nomorBarang = 0;
            std::cout << "Barang ingin dibeli: ";
            cin >> nomorBarang;

            if(mapIdxKode.find(nomorBarang) == mapIdxKode.end()){
                std::cout << "Nomor barang is invalid!" << std::endl;
            }else{
                validNomorBarang = true;
            }
        }

        int kuantitas;
        Asset* barang;
        bool validKuantitas = false;
        bool kuantitasCukup = false;
        while(!validKuantitas){
            kuantitas = 0;
            barang = nullptr;
            std::cout << "Kuantitas: ";
            cin >> kuantitas;

            if(kuantitas <= 0 || kuantitas > this->inventory.countAvailableCapacity()){
                std::cout << "Kuantitas is invalid!" << std::endl;
            }else{
                if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_MATERIAL_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!" << std::endl;
                    }else{
                        barang = ProductMaterial::configProdukMaterial[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_FRUIT_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]]->getNamaAsset() << "!" << std::endl;
                    }else{
                        barang = ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_HEWAN"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]]->getNamaAsset() << "!" << std::endl;
                    }else{
                        barang = ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "HEWAN"){
                    barang = Hewan::configHewan[mapIdxKode[nomorBarang]];
                    kuantitasCukup = true;
                }else if(mapType[mapIdxKode[nomorBarang]] == "TUMBUHAN"){
                    barang = Tumbuhan::configTumbuhan[mapIdxKode[nomorBarang]];
                    kuantitasCukup = true;
                }
            }

            if(kuantitasCukup){
                if(this->uang >= kuantitas * Toko::catalogPrice[mapIdxKode[nomorBarang]]){
                    std::cout << "Selamat! Anda berhasil membeli " << kuantitas << barang->getNamaAsset() << std::endl;
                    validKuantitas = true;
                }else{
                    std::cout << "You don't have enough money to buy that much!" << std::endl;
                }
            }
        }

        std::cout << "\nPilih slot untuk menyimpan barang yang Anda beli!" << std::endl;
        this->inventory.print();

        bool invalidPetakFound = true;
        vector<string> petakBeli;
        string petakBeliInput;
        while (invalidPetakFound){
            invalidPetakFound = false;

            petakBeliInput = "";
            std::cout << "Petak slot : ";
            cin >> petakBeliInput;
            petakBeli = Pemain::stringToArrayComma(petakBeliInput);

            for (const std::string& petak : petakBeli) {
                if (!this->inventory.isValidKey(petak)) {
                    invalidPetakFound = true;
                    std::cout << petak << " is invalid" << std::endl;
                }else if(this->inventory.get(petak) != nullptr){
                    invalidPetakFound = true;
                    std::cout << petak << " is not available" << std::endl;
                }
            }
        }

        for(const string& petak : petakBeli){
            this->inventory.setWithKey(petak, barang);

            if(dynamic_cast<ProductMaterial*>(barang)){
                Toko::catalogProduk[barang->getNamaAsset()]--;
            }else if(dynamic_cast<ProductFruit*>(barang) || dynamic_cast<ProductHewan*>(barang)){
                Toko::catalogProduk[barang->getKodeHuruf()]--;
            }
        }

        std::cout << barang->getNamaAsset() << " berhasil disimpan dalam penyimpanan!" << std::endl;
    }catch(uangInsufficientException& e){
        std::cout << e.what();
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

int Walikota::getNetWorth(){
    return this->inventory.getTotalWorth() + this->uang;
}

int Walikota::pungutPajak(vector<Pemain*> players){
    int total_pajak = 0;

    for(Pemain* player : players){
        int tax_deduction;

        if(player->countPajak() > player->getUang()){
            tax_deduction = player->getUang();
        }else{
            tax_deduction = player->countPajak();
        }

        total_pajak += tax_deduction;
        int taxed_money = player->getUang() - tax_deduction;
        player->setUang(taxed_money);
    }

    return total_pajak;
}

int Walikota::countPajak(){
    int kkp = this->getNetWorth();
    if(kkp <= 0){
        return 0;
    }else if(kkp <= 6){
        return 0.05 * kkp;
    }else if(kkp <= 25){
        return 0.15 * kkp;
    }else if(kkp <= 50){
        return 0.25 * kkp;
    }else if(kkp <= 500){
        return 0.3 * kkp;
    }else{
        return 0.35 * kkp;
    }
}
//<---------------PETERNAK----------------->
Peternak::Peternak(int peternakID, string username){
    this->peternakID = peternakID;
    this->username = username;
    this->uang = Pemain::defaultUang;
    this->beratBadan = Pemain::defaultBerat;
}

Peternak::Peternak(int peternakID, string username, int uang, int beratBadan, Inventory inventory, Peternakan peternakan){
    this->peternakID = peternakID;
    this->username = username;
    this->uang = uang;
    this->beratBadan = beratBadan;
    this->inventory = inventory;
    this->peternakan = peternakan;
}

Peternak::~Peternak(){
    //delete[] peternakan;
    //~Pemain();
}

Peternak::Peternak(Peternak& other){
    this->peternakID = peternakID;
    this->username = other.getUsername();
    this->uang = other.getUang();
    this->beratBadan = other.getBeratBadan();
    this->inventory = other.getInventory();
    this->peternakan = other.getPeternakan();
}

Peternak& Peternak::operator=(const Peternak& other){
    this->peternakID = other.peternakID;
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->inventory = other.inventory;
    this->peternakan = other.peternakan;
}

void Peternak::setPeternakID(int peternakID){
    this->peternakID = peternakID;
}

int Peternak::getPeternakID(){
    return this->peternakID;
}

Peternakan Peternak::getPeternakan(){
    return this->peternakan;
}

void Peternak::taruhHewan(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();

        if(this->inventory.getJumlahHewan() <= 0){
            throw noHewanAvailableException();
        }

        if(this->peternakan.isFull()){
            throw peternakanFullException();
        }

        std::cout << "Pilih hewan dari penyimpanan" << std::endl;
        this->inventory.print();

        string key_inv;
        bool validInv = false;
        while(!validInv){
            std::cout << "Slot : ";
            std::cin >> key_inv;

            if(!this->inventory.isValidKey(key_inv)){
                std::cout << key_inv << " is invalid" << std::endl;
            }else if(this->getFromInventory(key_inv) == nullptr){
                std::cout << key_inv << " is empty" << std::endl;
            }else if(!dynamic_cast<Hewan*>(this->getFromInventory(key_inv))){
                std::cout << "Object in " << key_inv << "is not of Hewan type" << std::endl;
            }else{
                validInv = true;
            }
        }

        Hewan* hewan = dynamic_cast<Hewan*>(this->getFromInventory(key_inv));

        std::cout << "Kamu memilih " << hewan->getNamaAsset() << std::endl;
        std::cout << "\nPilih petak peternakan yang akan ditinggali" << std::endl;
        this->peternakan.print();

        string key_peternakan;
        bool validPet = false;
        while(!validPet){
            std::cout << "Petak peternakan: ";
            std::cin >> key_peternakan;

            if(!this->inventory.isValidKey(key_peternakan)){
                std::cout << key_peternakan << " is invalid" << std::endl;
            }else if(this->peternakan.get(key_peternakan) != nullptr){
                std::cout << key_peternakan << " is not vacant" << std::endl;
            }else{
                validPet = true;
            }
        }

        this->peternakan.setWithKey(key_peternakan, hewan);
        this->inventory.setNull(key_inv);

        std::cout << "\nDengan hati-hati, kamu meletakkan seekor " << hewan->getNamaAsset() << " di kandang." << std::endl;
        std::cout << hewan->getNamaAsset() << " telah menjadi peliharaanmu sekarang!";
    }catch(inventoryEmptyException& e){
        std::cout << e.what();
    }catch(noHewanAvailableException& e){
        std::cout << e.what();
    }catch(peternakanFullException& e){
        std::cout << e.what();
    }
}

void Peternak::beriMakan(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();

        if(this->inventory.getJumlahProductFruit() == 0 && this->inventory.getJumlahProductHewan() == 0){
            throw noFoodException();
        }

        this->peternakan.cekPeternakan();

        if(this->peternakan.hasCarnivore()){
            if(!this->peternakan.hasHerbivore() && !this->peternakan.hasOmnivore()){
                if(this->inventory.getJumlahProductHewan() == 0){
                    throw noMatchingFoodException();
                }
            }
        }else{
            if(this->peternakan.hasHerbivore() && !this->peternakan.hasOmnivore()){
                if(this->inventory.getJumlahProductFruit() == 0){
                    throw noMatchingFoodException();
                }
            }
        }

        if(this->peternakan.isEmpty()){
            throw peternakanEmptyException();
        }

        std::cout << "Pilih petak kandang yang akan diberi makan" << std::endl;
        this->peternakan.print();

        string key_peternakan;
        bool validPet = false;
        while(!validPet){
            std::cout << "Petak peternakan: ";
            std::cin >> key_peternakan;

            if(!this->peternakan.isValidKey(key_peternakan)){
                std::cout << key_peternakan << " is invalid" << std::endl;
            }else if(this->peternakan.get(key_peternakan) == nullptr){
                std::cout << key_peternakan << " is empty";
            }else{
                validPet = true;
            }
        }

        std::cout << "Kamu memilih " << this->peternakan.get(key_peternakan)->getNamaAsset() << " untuk diberi makan." << std::endl;
        std::cout << "Pilih pangan yang akan diberikan" << std::endl;
        this->inventory.print();

        string slot;
        bool validInv = false;
        while(!validInv){
            std::cout << "Slot: ";
            std::cin >> slot;

            if(!this->inventory.isValidKey(slot)){
                std::cout << slot << " is invalid" << std::endl;
            }else if(this->getFromInventory(slot) == nullptr){
                std::cout << slot << " is empty" << std::endl;
            }else if(!dynamic_cast<ProductFruit*>(this->getFromInventory(slot)) && !dynamic_cast<ProductHewan*>(this->getFromInventory(slot))){
                std::cout << this->getFromInventory(slot)->getNamaAsset() << " is inedible" << std::endl;
            }else if(dynamic_cast<ProductFruit*>(this->getFromInventory(slot)) && dynamic_cast<Carnivore*>(this->peternakan.get(key_peternakan))){
                std::cout << "You are feeding " << this->getFromInventory(slot)->getNamaAsset() << " to "<< this->peternakan.get(key_peternakan) << ". Carnivore can't eat ProductFruit." << std::endl;
            }else if(dynamic_cast<ProductHewan*>(this->getFromInventory(slot)) && dynamic_cast<Herbivore*>(this->peternakan.get(key_peternakan))){
                std::cout << "You are feeding " << this->getFromInventory(slot)->getNamaAsset() << " to "<< this->peternakan.get(key_peternakan) << ". Herbivore can't eat ProductHewan." << std::endl;
            }else{
                validInv = true;
            }
        }

        Produk* pakan = dynamic_cast<Produk*>(this->getFromInventory(slot));
        this->peternakan.get(key_peternakan)->makan(pakan);
        this->inventory.setNull(slot);

        std::cout << this->peternakan.get(key_peternakan)->getNamaAsset() << " sudah diberi makan dan beratnya menjadi " << this->peternakan.get(key_peternakan)->getWeight() << "." << std::endl;
    }catch(inventoryEmptyException& e){
        std::cout << e.what();
    }catch(peternakanEmptyException& e){
        std::cout << e.what();
    }catch(noFoodException& e){
        std::cout << e.what();
    }catch(noMatchingFoodException& e){
        std::cout << e.what();
    }
}
  
void Peternak::panenHewan(){
    try{
        if(this->peternakan.isEmpty()){
            throw peternakanEmptyException();
        }

        if(!this->peternakan.isAvailablePanen()){
            throw noneSiapPanenPeternakanException();
        }

        if(!this->inventory.isFull()){
            throw inventoryFullException();
        }

        this->peternakan.print();

        map<string, int> rekapPeternakan = this->peternakan.rekapPeternakan();
        for(const auto& pair : rekapPeternakan){
            std::cout << "- " << pair.first << ": " << Hewan::configHewan[pair.first]->getNamaAsset() << std::endl;
        }

        std::cout << "\nPilih hewan siap panen yang kamu miliki" << std::endl;
        int idx = 0;
        map<int, string> mapIdxKode;
        for(const auto& pair : rekapPeternakan){
            if(pair.second > 0){
                std::cout << ++idx << ". " << pair.first << " (" << pair.second << " petak siap panen)" << std::endl;
                mapIdxKode.insert({idx, pair.first});
            }
        }

        int nomor_hewan;
        bool validNomorHewan = false;
        while(!validNomorHewan){
            nomor_hewan = 0;
            std::cout << "Nomor hewan yang ingin dipanen: ";
            std::cin >> nomor_hewan;

            if(mapIdxKode.find(nomor_hewan) == mapIdxKode.end()){
                std::cout << "Nomor hewan is invalid!\n" << std::endl;
            }else{
                validNomorHewan = true;
            }
        }
        
        int jumlah_petak;
        bool validJumlahPetak = false;
        while(!validJumlahPetak){
            jumlah_petak = 0;
            std::cout << "\nJumlah petak yang ingin dipanen: ";
            std::cin >> jumlah_petak;

            if(jumlah_petak <= 0){
                std::cout << "Jumlah petak is invalid!\n";
            }else if(jumlah_petak > rekapPeternakan[mapIdxKode[nomor_hewan]]){
                std::cout << "You are trying to harvest more than the amount of petak that is currently available to harvest!\n";
            }else if(this->inventory.countAvailableCapacity() < jumlah_petak){
                std::cout << "Available inventory capacity is not enough!\n";
            }else{
                validJumlahPetak = true;
            }
        }

        std::cout << "\nPilih petak yang ingin dipanen:" << std::endl;
        string str_key = "";
        vector<string> key_vec;

        for(int i = 1; i <= jumlah_petak; i++){
            string temp_key;
            bool validTempKey = false;
            while(!validTempKey){
                temp_key = "";
                
                std::cout << "Petak ke-" << i << ": ";
                std::cin >> temp_key;

                if(!this->peternakan.isValidKey(temp_key)){
                    std::cout << temp_key << " is invalid" << std::endl;
                }else if(this->peternakan.get(temp_key) == nullptr){
                    std::cout << temp_key << " is empty" << std::endl;
                }else if(this->peternakan.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_hewan]){
                    std::cout << temp_key << " doesn't contain " << mapIdxKode[nomor_hewan] << "." << std::endl;
                }else{
                    key_vec.push_back(temp_key);
                    validTempKey = true;
                }
            }

            if(i == 1){
                str_key += temp_key;
            }else{
                str_key = str_key + ", " + temp_key;
            }
        }

        for(string key : key_vec){
            this->inventory.addItem(this->peternakan.get(key));
            this->peternakan.setNull(key);
        }

        std::cout << jumlah_petak << " petak hewan " << mapIdxKode[nomor_hewan] << " pada petak " << str_key << " telah dipanen." << std::endl;
    }catch(peternakanEmptyException& e){
        std::cout << e.what();
    }catch(noneSiapPanenPeternakanException& e){
        std::cout << e.what();
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

void Peternak::beliAsset(Toko* store){
    try{
        if(store->findCheapest() > this->uang){
            throw uangInsufficientException();
        }

        if(this->inventory.isFull()){
            throw inventoryFullException();
        }

        std::cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda beli" << endl;
        int idx = 0;
        map<int, string> mapIdxKode;
        map<string, string> mapType;
        for(const auto& pair : Toko::catalogBangunan){
            if(pair.second > 0){
                std::cout << ++idx << ". " << pair.first << " - " << Bangunan::resepBangunan[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                mapIdxKode.insert({idx, pair.first});
                mapType.insert({pair.first, Bangunan::resepBangunan[pair.first]->getAssetType()});
            }
        }

        for(const auto& pair : Toko::catalogProduk){
            if(ProductMaterial::configProdukMaterial.find(pair.first) != ProductMaterial::configProdukMaterial.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << pair.first << " - " << ProductMaterial::configProdukMaterial[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductMaterial::configProdukMaterial[pair.first]->getProdukType()});
                }
            }else if(ProductFruit::configProdukFruit.find(pair.first) != ProductFruit::configProdukFruit.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << ProductFruit::configProdukFruit[pair.first]->getNamaAsset() << " - " << ProductFruit::configProdukFruit[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductFruit::configProdukFruit[pair.first]->getProdukType()});
                }
            }else if(ProductHewan::configProdukHewan.find(pair.first) != ProductHewan::configProdukHewan.end()){
                if(pair.second > 0){
                    std::cout << ++idx << ". " << ProductHewan::configProdukHewan[pair.first]->getNamaAsset() << " - " << ProductHewan::configProdukHewan[pair.first]->getPrice() << " (" << pair.second << ")" << std::endl;
                    mapIdxKode.insert({idx, pair.first});
                    mapType.insert({pair.first, ProductHewan::configProdukHewan[pair.first]->getProdukType()});
                }
            }
        }

        for(string hewan : Toko::catalogHewan){
            std::cout << ++idx << ". " << Hewan::configHewan[hewan]->getNamaAsset() << " - " << Hewan::configHewan[hewan]->getPrice() << std::endl;
            mapIdxKode.insert({idx, hewan});
            mapType.insert({hewan, Hewan::configHewan[hewan]->getAssetType()});
        }

        for(string tumbuhan : Toko::catalogTumbuhan){
            std::cout << ++idx << ". " << Tumbuhan::configTumbuhan[tumbuhan]->getNamaAsset() << " - " << Tumbuhan::configTumbuhan[tumbuhan]->getPrice() << std::endl;
            mapIdxKode.insert({idx, tumbuhan});
            mapType.insert({tumbuhan, Tumbuhan::configTumbuhan[tumbuhan]->getAssetType()});
        }

        std::cout << "Uang Anda: " << this->getUang() << std::endl;
        std::cout << "Slot penyimpanan tersedia: " << this->inventory.countAvailableCapacity() << std::endl;

        int nomorBarang;
        bool validNomorBarang = false;
        while(!validNomorBarang){
            nomorBarang = 0;
            std::cout << "Barang ingin dibeli: ";
            cin >> nomorBarang;

            if(mapIdxKode.find(nomorBarang) == mapIdxKode.end()){
                std::cout << "Nomor barang is invalid!" << std::endl;
            }else{
                validNomorBarang = true;
            }
        }

        int kuantitas;
        Asset* barang;
        bool validKuantitas = false;
        bool kuantitasCukup = false;
        while(!validKuantitas){
            kuantitas = 0;
            barang = nullptr;
            std::cout << "Kuantitas: ";
            cin >> kuantitas;

            if(kuantitas <= 0){
                std::cout << "Kuantitas is invalid!" << std::endl;
            }else{
                if(mapType[mapIdxKode[nomorBarang]] == "BANGUNAN"){
                    if(kuantitas > Toko::catalogBangunan[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!" << std::endl;
                    }else{
                        barang = Bangunan::resepBangunan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_MATERIAL_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!" << std::endl;
                    }else{
                        barang = ProductMaterial::configProdukMaterial[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_FRUIT_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]]->getNamaAsset() << "!" << std::endl;
                    }else{
                        barang = ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_HEWAN"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << "There isn't enough stock of " << ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]]->getNamaAsset() << "!" << std::endl;
                    }else{
                        barang = ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "HEWAN"){
                    barang = Hewan::configHewan[mapIdxKode[nomorBarang]];
                    kuantitasCukup = true;
                }else if(mapType[mapIdxKode[nomorBarang]] == "TUMBUHAN"){
                    barang = Tumbuhan::configTumbuhan[mapIdxKode[nomorBarang]];
                    kuantitasCukup = true;
                }else{
                    cout << "bocor sini" << endl;
                }
            }

            cout << "Kuantitas cukup " << kuantitasCukup << endl;

            if(kuantitasCukup){
                if(this->uang >= kuantitas * Toko::catalogPrice[mapIdxKode[nomorBarang]]){
                    std::cout << "Selamat! Anda berhasil membeli " << kuantitas << barang->getNamaAsset() << std::endl;
                    validKuantitas = true;
                }else{
                    std::cout << "You don't have enough money to buy that much!" << std::endl;
                }
            }else{
                cout << "Malah ke sini wkwkwk!" << endl;
            }
        }

        std::cout << "\nPilih slot untuk menyimpan barang yang Anda beli!" << std::endl;
        this->inventory.print();

        bool invalidPetakFound = true;
        vector<string> petakBeli;
        string petakBeliInput;
        while (invalidPetakFound){
            invalidPetakFound = false;

            petakBeliInput = "";
            std::cout << "Petak slot : ";
            cin >> petakBeliInput;
            petakBeli = Pemain::stringToArrayComma(petakBeliInput);

            for (const std::string& petak : petakBeli) {
                if (!this->inventory.isValidKey(petak)) {
                    invalidPetakFound = true;
                    std::cout << petak << " is invalid" << std::endl;
                }else if(this->inventory.get(petak) != nullptr){
                    invalidPetakFound = true;
                    std::cout << petak << " is not available" << std::endl;
                }
            }
        }

        for(const string& petak : petakBeli){
            this->inventory.setWithKey(petak, barang);
            if(dynamic_cast<Bangunan*>(barang)){
                Toko::catalogBangunan[barang->getNamaAsset()]--;
            }else if(dynamic_cast<ProductMaterial*>(barang)){
                Toko::catalogProduk[barang->getNamaAsset()]--;
            }else if(dynamic_cast<ProductFruit*>(barang) || dynamic_cast<ProductHewan*>(barang)){
                Toko::catalogProduk[barang->getKodeHuruf()]--;
            }
        }

        std::cout << barang->getNamaAsset() << " berhasil disimpan dalam penyimpanan!" << std::endl;
    }catch(uangInsufficientException& e){
        std::cout << e.what();
    }catch(inventoryFullException& e){
        std::cout << e.what();
    }
}

int Peternak::getNetWorth() {
    return this->inventory.getTotalWorth() + this->peternakan.getTotalWorth() + this->uang;
}

int Peternak::countPajak(){
    int kkp = this->getNetWorth() - this->ktkp;
    if(kkp <= 0){
        return 0;
    }else if(kkp <= 6){
        return 0.05 * kkp;
    }else if(kkp <= 25){
        return 0.15 * kkp;
    }else if(kkp <= 50){
        return 0.25 * kkp;
    }else if(kkp <= 500){
        return 0.3 * kkp;
    }else{
        return 0.35 * kkp;
    }
}
