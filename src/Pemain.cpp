#include "Pemain.hpp"
#include <iostream>
#include <cctype>
using namespace std;

int Pemain::uangWin;
int Pemain::beratWin;
//<---------------PEMAIN----------------->
std::vector<std::string> Pemain::stringToArrayComma(const std::string& input) {
    // Remove white spaces from the input string
    std::string inputWithoutSpaces = input;
    inputWithoutSpaces.erase(std::remove_if(inputWithoutSpaces.begin(), inputWithoutSpaces.end(), ::isspace), inputWithoutSpaces.end());

    // Tokenize the modified string using commas as delimiters
    std::vector<std::string> result;
    std::stringstream ss(inputWithoutSpaces);
    std::string token;
    while (std::getline(ss, token, ',')) {
        if (!token.empty()) {  // Check if token is not empty
            result.push_back(token);
        }
    }
    return result;
}

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
        while(invalidPetakFound){
            invalidPetakFound = false;

            petakJualInput = "";
            cin.get();
            std::cout << "\nSilahkan pilih petak yang ingin Anda jual!\nPetak : ";
            getline(cin, petakJualInput);
            petakJual = Pemain::stringToArrayComma(petakJualInput);

            for (const std::string& petak : petakJual) {
                if (!this->inventory.isValidKey(petak)) {
                    invalidPetakFound = true;
                    std::cout << YELLOW << petak << " is invalid" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(this->inventory.get(petak) == nullptr){
                    invalidPetakFound = true;
                    std::cout << YELLOW << petak << " is empty" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }
            }
        }

        int uangTambah = 0;
        for(const string& petak : petakJual){
            Asset* assetptr = this->inventory.get(petak);
            if(dynamic_cast<Hewan*>(assetptr) || dynamic_cast<Tumbuhan*>(assetptr)){
                this->uang += assetptr->getPrice();
                uangTambah += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<Bangunan*>(assetptr)){
                Toko::catalogBangunan[assetptr->getNamaAsset()]++;
                this->uang += assetptr->getPrice();
                uangTambah += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<ProductMaterial*>(assetptr)){
                Toko::catalogProduk[assetptr->getNamaAsset()]++;
                this->uang += assetptr->getPrice();
                uangTambah += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<ProductFruit*>(assetptr) || dynamic_cast<ProductHewan*>(assetptr)){
                Toko::catalogProduk[assetptr->getKodeHuruf()]++;
                this->uang += assetptr->getPrice();
                uangTambah += assetptr->getPrice();
                this->inventory.setNull(petak);
            }
        }

        cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << uangTambah << " gulden!" << endl;  
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

        this->inventory.print();

        string slot;
        bool validInv = false;
        while(!validInv){
            std::cout << "Slot: ";
            std::cin >> slot;

            if(!this->inventory.isValidKey(slot)){
                std::cout << YELLOW << slot << " is invalid\n" << NORMAL << std::endl;
            }else if(this->getFromInventory(slot) == nullptr){
                std::cout << YELLOW << slot << " is empty\n" << NORMAL << std::endl;
            }else if(!dynamic_cast<ProductFruit*>(this->getFromInventory(slot)) && !dynamic_cast<ProductHewan*>(this->getFromInventory(slot))){
                std::cout << YELLOW << this->getFromInventory(slot)->getNamaAsset() << " is inedible\n" << NORMAL << std::endl;
            }else{
                validInv = true;
            }
        }

        Produk* makanan = dynamic_cast<Produk*>(this->inventory.get(slot));
        this->setberatBadan(this->getBeratBadan() + makanan->getAddedWeight());
        this->inventory.setNull(slot);

        std::cout << "Dengan lahapnya, kamu memakan " << makanan->getNamaAsset() << " itu..." << std::endl;
        std::cout << "Alhasil, berat badan kamu " << GREEN << "naik menjadi " << this->getBeratBadan() << NORMAL << std::endl;
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

void Petani::printLadang(){
    this->ladang.print();
}

void Petani::tanamTanaman(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();

        if(this->inventory.getJumlahTumbuhan() <= 0){
            throw noTumbuhanAvailableException();
        }

        if(this->ladang.isFull()){
            throw ladangFullException();
        }

        std::cout << "Pilih tanaman dari penyimpanan" << std::endl;
        this->inventory.print();
        
        bool invalidSlotFound = true;
        vector<string> slotTanam;
        string slotTanamInput;
        while (invalidSlotFound){
            invalidSlotFound = false;
            slotTanam.clear();

            slotTanamInput = "";
            cin.get();
            std::cout << "Slot : ";
            getline(cin, slotTanamInput);
            slotTanam = Pemain::stringToArrayComma(slotTanamInput);

            for (string petak : slotTanam){
                if (!this->inventory.isValidKey(petak)) {
                    invalidSlotFound = true;
                    std::cout << YELLOW << petak << " is invalid" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(this->inventory.get(petak) == nullptr){
                    invalidSlotFound = true;
                    std::cout << YELLOW << petak << " is empty" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(!dynamic_cast<Tumbuhan*>(this->inventory.get(petak))){
                    invalidSlotFound = true;
                    std::cout << YELLOW << petak << " doesn't contain Tumbuhan" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }
            }
        }

        vector<Tumbuhan*> tumbuhanTanam;
        for(const string& key_inv : slotTanam){
            if(dynamic_cast<MaterialPlant*>(this->getFromInventory(key_inv))){
                MaterialPlant* tumbuhan = new MaterialPlant(*dynamic_cast<MaterialPlant*>(this->getFromInventory(key_inv)));
                tumbuhanTanam.push_back(tumbuhan);
                std::cout << "Kamu memilih " << tumbuhan->getNamaAsset() << " pada " << key_inv << std::endl;
            }else if(dynamic_cast<FruitPlant*>(this->getFromInventory(key_inv))){
                FruitPlant* tumbuhan = new FruitPlant(*dynamic_cast<FruitPlant*>(this->getFromInventory(key_inv)));
                tumbuhanTanam.push_back(tumbuhan);
                std::cout << "Kamu memilih " << tumbuhan->getNamaAsset() << " pada " << key_inv << std::endl;
            }

            this->inventory.setNull(key_inv);
        }

        std::cout << "\nPilih petak yang akan ditanami" << std::endl;
        this->ladang.print();

        for(Tumbuhan* tanaman : tumbuhanTanam){
            string key_ladang;
            bool validLad = false;
            while(!validLad){
                std::cout << "Tanaman: " << tanaman->getNamaAsset() << endl;
                std::cout << "Petak tanah: ";
                std::cin >> key_ladang;

                if(!this->ladang.isValidKey(key_ladang)){
                    std::cout << YELLOW << key_ladang << " is invalid\n" << NORMAL << std::endl;
                }else if(this->ladang.get(key_ladang) != nullptr){
                    std::cout << YELLOW << key_ladang << " is not vacant\n" << NORMAL << std::endl;
                }else{
                    validLad = true;
                }
            }

            tanaman->setTurnInstantiated(Tumbuhan::current_turn);
            this->ladang.setWithKey(key_ladang, tanaman);

            std::cout << "\nCangkul, cangkul, cangkul yang dalam~!" << std::endl;
            std::cout << GREEN << tanaman->getNamaAsset() << " berhasil ditanam!\n" << NORMAL << endl;
        }
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

        if(this->inventory.isFull()){
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
            std::string input;
            std::cout << "Nomor tanaman yang ingin dipanen: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            nomor_tanaman = std::stoi(input);
            if(mapIdxKode.find(nomor_tanaman) == mapIdxKode.end()){
                std::cout << YELLOW << "Nomor tanaman is invalid!\n" << NORMAL << std::endl;
            }else{
                validNomorTanaman = true;
            }
        }

        vector<Produk*> produkHasil;
        string type = Tumbuhan::configTumbuhan[mapIdxKode[nomor_tanaman]]->getTumbuhanType();
        string nama_tumbuhan = Tumbuhan::configTumbuhan[mapIdxKode[nomor_tanaman]]->getNamaAsset();

        if(type == "MATERIAL_PLANT"){
            for(const auto& pair : ProductMaterial::configProdukMaterial){
                if(pair.second->getOrigin() == nama_tumbuhan){
                    produkHasil.push_back(pair.second);
                }
            }
        }else if(type == "FRUIT_PLANT"){
            for(const auto& pair : ProductFruit::configProdukFruit){
                if(pair.second->getOrigin() == nama_tumbuhan){
                    produkHasil.push_back(pair.second);
                }
            }
        }

        int jumlah_petak;
        bool validJumlahPetak = false;
        while(!validJumlahPetak){
            jumlah_petak = 0;
            std::string input;
            std::cout << "\nJumlah petak yang ingin dipanen: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            
            jumlah_petak = std::stoi(input);
            if(jumlah_petak <= 0){
                std::cout << YELLOW << "Jumlah petak is invalid!\n" << NORMAL << endl;
            }else if(jumlah_petak > rekapLadang[mapIdxKode[nomor_tanaman]]){
                std::cout << YELLOW << "You are trying to harvest more than the amount of petak that is currently available to harvest!\n" << NORMAL << endl;
            }else if(this->inventory.countAvailableCapacity() < (jumlah_petak * produkHasil.size())){
                std::cout << YELLOW << "Available inventory capacity is not enough!\n" << endl;
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
                    std::cout << YELLOW << temp_key << " is invalid\n" << NORMAL << std::endl;
                }else if(this->ladang.get(temp_key) == nullptr){
                    std::cout << YELLOW << temp_key << " is empty\n" << NORMAL << std::endl;
                }else if(this->ladang.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_tanaman]){
                    std::cout << YELLOW << temp_key << " doesn't contain " << mapIdxKode[nomor_tanaman] << ".\n" << NORMAL << std::endl;
                }else if(!this->ladang.get(temp_key)->isReadyToHarvest()){
                    std::cout << YELLOW << mapIdxKode[nomor_tanaman] << " in " << temp_key << " is not ripe yet.\n" << NORMAL << std::endl;
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
            for(Produk* produk : produkHasil){
                this->inventory.addItem(produk);
            }
            this->ladang.setNull(key);
        }

        std::cout << GREEN << jumlah_petak << " petak tanaman " << mapIdxKode[nomor_tanaman] << " pada petak " << str_key << " telah dipanen." << NORMAL << std::endl;
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
        while (!validNomorBarang) {
            nomorBarang = 0;
            std::string input;
            std::cout << "Barang ingin dibeli: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            nomorBarang = std::stoi(input);
            if (mapIdxKode.find(nomorBarang) == mapIdxKode.end() || nomorBarang <= 0) {
                std::cout << YELLOW << "Nomor barang is invalid!\n" << NORMAL << std::endl;
            } else if (Toko::catalogPrice[mapIdxKode[nomorBarang]] > this->uang) {
                std::cout << YELLOW << "Barang is too expensive!\n" << NORMAL << std::endl;
            } else {
                validNomorBarang = true;
            }
        }

        int kuantitas;
        Asset* barang;
        bool validKuantitas = false;
        bool kuantitasCukup;
        while(!validKuantitas){
            kuantitas = 0;
            kuantitasCukup = false;
            barang = nullptr;
            std::string input;
            std::cout << "Kuantitas: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            kuantitas = std::stoi(input);
            if(kuantitas <= 0){
                std::cout << YELLOW << "Kuantitas is invalid!\n" << NORMAL << std::endl;
            }else if(kuantitas > this->inventory.countAvailableCapacity()){
                cout << YELLOW << "Inventory capacity is not enough" << NORMAL << endl;
            }else{
                if(mapType[mapIdxKode[nomorBarang]] == "BANGUNAN"){
                    if(kuantitas > Toko::catalogBangunan[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!\n" << NORMAL << std::endl;
                    }else{
                        barang = Bangunan::resepBangunan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_MATERIAL_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!\n" << NORMAL << std::endl;
                    }else{
                        barang = ProductMaterial::configProdukMaterial[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_FRUIT_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]]->getNamaAsset() << "!\n" << NORMAL << std::endl;
                    }else{
                        barang = ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_ANIMAL"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]]->getNamaAsset() << "!\n" << NORMAL << std::endl;
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
                    std::cout << GREEN << "Selamat! Anda berhasil membeli " << kuantitas << " " << barang->getNamaAsset() << NORMAL << std::endl;
                    validKuantitas = true;
                }else{
                    std::cout << YELLOW << "You don't have enough money to buy that much!\n" << NORMAL << std::endl;
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
            petakBeli.clear();

            petakBeliInput = "";
            cin.get();
            std::cout << "Petak slot : ";
            getline(cin, petakBeliInput);
            petakBeli = Pemain::stringToArrayComma(petakBeliInput);

            if (petakBeli.size() == kuantitas){
                for (string petak : petakBeli){
                    if (!this->inventory.isValidKey(petak)) {
                        invalidPetakFound = true;
                        std::cout << YELLOW << petak << " is invalid" << std::endl;
                        std::cout << "Press any key to continue..." << NORMAL << endl;
                    }else if(this->inventory.get(petak) != nullptr){
                        invalidPetakFound = true;
                        std::cout << YELLOW << petak << " is not available" << std::endl;
                        std::cout << "Press any key to continue..." << NORMAL << endl;
                    }
                }
            }else{
                invalidPetakFound = true;
                std::cout << YELLOW << "You are trying to buy " << kuantitas << " assets, but input " << petakBeli.size() << " slots" << endl;
                std::cout << "Please input " << kuantitas << " slots" << endl;
                std::cout << "Press any key to continue..." << NORMAL << endl;
            }
        }

        for(const string& petak : petakBeli){
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
            string input;
            std::cout << "Barang ingin dibeli: ";
            cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            nomorBarang = std::stoi(input);
            if(mapIdxKode.find(nomorBarang) == mapIdxKode.end() || nomorBarang <= 0){
                std::cout << YELLOW << "Nomor barang is invalid!" << NORMAL << std::endl;
            }else if(Toko::catalogPrice[mapIdxKode[nomorBarang]] > this->uang){
                std::cout << YELLOW << "Barang is too expensive!" << NORMAL << std::endl;
            }else{
                validNomorBarang = true;
            }
        }

        int kuantitas;
        Asset* barang;
        bool validKuantitas = false;
        bool kuantitasCukup;
        while(!validKuantitas){
            kuantitas = 0;
            kuantitasCukup = false;
            barang = nullptr;
            std::string input;
            std::cout << "Kuantitas: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            kuantitas = std::stoi(input);
            if(kuantitas <= 0){
                std::cout << YELLOW <<  "Kuantitas is invalid!" << NORMAL << std::endl;
            }else if(kuantitas > this->inventory.countAvailableCapacity()){
                cout << YELLOW << "Inventory capacity is not enough" << NORMAL << endl;
            }else{
                if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_MATERIAL_PLANT"){
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
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_ANIMAL"){
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
                }
            }

            if(kuantitasCukup){
                if(this->uang >= kuantitas * Toko::catalogPrice[mapIdxKode[nomorBarang]]){
                    std::cout << GREEN << "Selamat! Anda berhasil membeli " << kuantitas << barang->getNamaAsset() << NORMAL << std::endl;
                    validKuantitas = true;
                }else{
                    std::cout << YELLOW << "You don't have enough money to buy that much!" << NORMAL << std::endl;
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
            petakBeli.clear();

            petakBeliInput = "";
            cin.get();
            std::cout << "Petak slot : ";
            getline(cin, petakBeliInput);
            petakBeli = Pemain::stringToArrayComma(petakBeliInput);

            if(petakBeli.size() == kuantitas){
                for (const std::string& petak : petakBeli) {
                    if (!this->inventory.isValidKey(petak)) {
                        invalidPetakFound = true;
                        std::cout << YELLOW <<  petak << " is invalid" << std::endl;
                        std::cout << "Press any key to continue..." << NORMAL << endl;
                    }else if(this->inventory.get(petak) != nullptr){
                        invalidPetakFound = true;
                        std::cout << YELLOW << petak << " is not available" << std::endl;
                        std::cout << "Press any key to continue..." << NORMAL << endl;
                    }
                }
            }else{
                invalidPetakFound = true;
                std::cout << YELLOW << "You are trying to buy " << kuantitas << " assets, but input " << petakBeli.size() << " slots" << endl;
                std::cout << "Please input " << kuantitas << " slots" << endl;
                std::cout << "Press any key to continue..." << NORMAL << endl;
            }
        }

        for(const string& petak : petakBeli){
            this->inventory.setWithKey(petak, barang);
            this->uang -= barang->getPrice();

            if(dynamic_cast<ProductMaterial*>(barang)){
                Toko::catalogProduk[barang->getNamaAsset()]--;
            }else if(dynamic_cast<ProductFruit*>(barang) || dynamic_cast<ProductHewan*>(barang)){
                Toko::catalogProduk[barang->getKodeHuruf()]--;
            }
        }

        std::cout << GREEN << barang->getNamaAsset() << " berhasil disimpan dalam penyimpanan!" << std::endl;
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

void Peternak::printPeternakan(){
    this->peternakan.print();
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

        bool invalidSlotFound = true;
        vector<string> slotTernak;
        string slotTernakInput;
        while(invalidSlotFound){
            invalidSlotFound = false;
            slotTernak.clear();

            slotTernakInput = "";
            cin.get();
            std::cout << "Slot : ";
            getline(cin, slotTernakInput);
            slotTernak = Pemain::stringToArrayComma(slotTernakInput);

            for(string kandang : slotTernak){
                if(!this->inventory.isValidKey(kandang)){
                    invalidSlotFound = true;
                    std::cout << YELLOW << kandang << " is invalid" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(this->getFromInventory(kandang) == nullptr){
                    invalidSlotFound = true;
                    std::cout << YELLOW << kandang << " is empty" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(!dynamic_cast<Hewan*>(this->getFromInventory(kandang))){
                    invalidSlotFound = true;
                    std::cout << YELLOW << kandang << " doesn't contain Hewan" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }
            }
        }

        vector<Hewan*> hewanTernak;
        for(const string& key_inv : slotTernak){
            if(dynamic_cast<Carnivore*>(this->getFromInventory(key_inv))){
                Carnivore* hewan = new Carnivore(*dynamic_cast<Carnivore*>(this->getFromInventory(key_inv)));
                hewanTernak.push_back(hewan);
                std::cout << "Kamu memilih " << hewan->getNamaAsset() << " pada " << key_inv << std::endl;
            }else if(dynamic_cast<Herbivore*>(this->getFromInventory(key_inv))){
                Herbivore* hewan = new Herbivore(*dynamic_cast<Herbivore*>(this->getFromInventory(key_inv)));
                hewanTernak.push_back(hewan);
                std::cout << "Kamu memilih " << hewan->getNamaAsset() << " pada " << key_inv << std::endl;
            }else if(dynamic_cast<Omnivore*>(this->getFromInventory(key_inv))){
                Omnivore* hewan = new Omnivore(*dynamic_cast<Omnivore*>(this->getFromInventory(key_inv)));
                hewanTernak.push_back(hewan);
                std::cout << "Kamu memilih " << hewan->getNamaAsset() << " pada " << key_inv << std::endl;
            }

            this->inventory.setNull(key_inv);
        }

        std::cout << "\nPilih petak peternakan yang akan ditinggali" << std::endl;
        this->peternakan.print();

        for(Hewan* hewan : hewanTernak){
            string key_peternakan;
            bool validPet = false;
            while(!validPet){
                std::cout << "Hewan: " << hewan->getNamaAsset() << endl;
                std::cout << "Petak peternakan: ";
                std::cin >> key_peternakan;

                if(!this->inventory.isValidKey(key_peternakan)){
                    std::cout << YELLOW << key_peternakan << " is invalid\n" << NORMAL << std::endl;
                }else if(this->peternakan.get(key_peternakan) != nullptr){
                    std::cout << YELLOW << key_peternakan << " is not vacant\n" << NORMAL << std::endl;
                }else{
                    validPet = true;
                }
            }

            this->peternakan.setWithKey(key_peternakan, hewan);

            std::cout << "\nDengan hati-hati, kamu meletakkan seekor " << hewan->getNamaAsset() << " di kandang." << std::endl;
            std::cout << GREEN << hewan->getNamaAsset() << " telah menjadi peliharaanmu sekarang!\n" << NORMAL << endl;
        }
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

        if(this->peternakan.isEmpty()){
            throw peternakanEmptyException();
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
        
        std::cout << "Pilih petak kandang yang akan diberi makan" << std::endl;
        this->peternakan.print();

        bool invalidSlotFound = true;
        vector<string> slotTernak;
        string slotTernakInput;
        while(invalidSlotFound){
            invalidSlotFound = false;
            slotTernak.clear();

            slotTernakInput = "";
            cin.get();
            std::cout << "Petak peternakan: ";
            getline(cin, slotTernakInput);
            slotTernak = Pemain::stringToArrayComma(slotTernakInput);

            for(string key_peternakan : slotTernak){
                if(!this->peternakan.isValidKey(key_peternakan)){
                    invalidSlotFound = true;
                    std::cout << YELLOW << key_peternakan << " is invalid" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(this->peternakan.get(key_peternakan) == nullptr){
                    invalidSlotFound = true;
                    std::cout << YELLOW << key_peternakan << " is empty" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }else if(!dynamic_cast<Hewan*>(this->peternakan.get(key_peternakan))){
                    invalidSlotFound = true;
                    std::cout << YELLOW << key_peternakan << " doesn't contain Hewan" << std::endl;
                    std::cout << "Press any key to continue..." << NORMAL << endl;
                }
            }
        }

        std::cout << std::endl;
        for(const string& slotHewan : slotTernak){
            std::cout << "Kamu memilih " << this->peternakan.get(slotHewan)->getNamaAsset() << " pada " << slotHewan << " untuk diberi makan." << std::endl;
        }

        std::cout << "Pilih pangan yang akan diberikan" << std::endl;
        this->inventory.print();
        
        for(const string& slotHewan : slotTernak){
            string slotInv;
            bool validInv = false;
            while(!validInv){
                std::cout << "Hewan: " << this->peternakan.get(slotHewan)->getNamaAsset() << endl;
                std::cout << "Slot: ";
                std::cin >> slotInv;

                if(!this->inventory.isValidKey(slotInv)){
                    std::cout << YELLOW << slotInv << " is invalid" << NORMAL << std::endl;
                }else if(this->getFromInventory(slotInv) == nullptr){
                    std::cout << YELLOW << slotInv << " is empty" << NORMAL << std::endl;
                }else if(!dynamic_cast<ProductFruit*>(this->getFromInventory(slotInv)) && !dynamic_cast<ProductHewan*>(this->getFromInventory(slotInv))){
                    std::cout << YELLOW << this->getFromInventory(slotInv)->getNamaAsset() << " is inedible\n" << NORMAL << std::endl;
                }else if(dynamic_cast<ProductFruit*>(this->getFromInventory(slotInv)) && dynamic_cast<Carnivore*>(this->peternakan.get(slotHewan))){
                    std::cout << YELLOW << "You are feeding " << this->getFromInventory(slotInv)->getNamaAsset() << " to "<< this->peternakan.get(slotHewan)->getNamaAsset() << ". Carnivore can't eat ProductFruit.\n" << NORMAL << std::endl;
                }else if(dynamic_cast<ProductHewan*>(this->getFromInventory(slotInv)) && dynamic_cast<Herbivore*>(this->peternakan.get(slotHewan))){
                    std::cout << YELLOW << "You are feeding " << this->getFromInventory(slotInv)->getNamaAsset() << " to "<< this->peternakan.get(slotHewan)->getNamaAsset() << ". Herbivore can't eat ProductHewan.\n" << NORMAL << std::endl;
                }else{
                    validInv = true;
                }
            }

            //aterialPlant* tumbuhan = new MaterialPlant(*dynamic_cast<MaterialPlant*>(this->getFromInventory(key_inv)));
            if(dynamic_cast<ProductFruit*>(this->getFromInventory(slotInv))){
                ProductFruit* pakan = new ProductFruit(*dynamic_cast<ProductFruit*>(this->getFromInventory(slotInv)));
                this->peternakan.get(slotHewan)->makan(pakan);
                this->inventory.setNull(slotInv);
                std::cout << this->peternakan.get(slotHewan)->getNamaAsset() << " sudah diberi makan dan " << GREEN << "beratnya menjadi " << this->peternakan.get(slotHewan)->getWeight() << "." << NORMAL << std::endl;
            }else if(dynamic_cast<ProductHewan*>(this->getFromInventory(slotInv))){
                ProductHewan* pakan = new ProductHewan(*dynamic_cast<ProductHewan*>(this->getFromInventory(slotInv)));
                this->peternakan.get(slotHewan)->makan(pakan);
                this->inventory.setNull(slotInv);
                std::cout << this->peternakan.get(slotHewan)->getNamaAsset() << " sudah diberi makan dan " << GREEN << "beratnya menjadi " << this->peternakan.get(slotHewan)->getWeight() << "." << NORMAL << std::endl;
            }
        }
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

        if(this->inventory.isFull()){
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
            std::string input;
            std::cout << "Nomor hewan yang ingin dipanen: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            nomor_hewan = std::stoi(input);
            if(mapIdxKode.find(nomor_hewan) == mapIdxKode.end()){
                std::cout << YELLOW << "Nomor hewan is invalid!\n" << NORMAL << std::endl;
            }else{
                validNomorHewan = true;
            }
        }

        vector<Produk*> produkHasil;
        string nama_hewan = Hewan::configHewan[mapIdxKode[nomor_hewan]]->getNamaAsset();
        for(const auto& pair : ProductHewan::configProdukHewan){
            if(pair.second->getOrigin() == nama_hewan){
                produkHasil.push_back(pair.second);
            }
        }
        
        int jumlah_petak;
        bool validJumlahPetak = false;
        while(!validJumlahPetak){
            jumlah_petak = 0;
            std::string input;
            std::cout << "\nJumlah petak yang ingin dipanen: ";
            std::cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            jumlah_petak = std::stoi(input);
            if(jumlah_petak <= 0){
                std::cout << YELLOW << "Jumlah petak is invalid!\n" << NORMAL << endl;
            }else if(jumlah_petak > rekapPeternakan[mapIdxKode[nomor_hewan]]){
                std::cout << YELLOW << "You are trying to harvest more than the amount of petak that is currently available to harvest!\n" << NORMAL << endl;
            }else if(this->inventory.countAvailableCapacity() < (jumlah_petak * produkHasil.size())){
                std::cout << YELLOW << "Available inventory capacity is not enough!\n" << NORMAL << endl;
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
                    std::cout << YELLOW << temp_key << " is invalid" << NORMAL << std::endl;
                }else if(this->peternakan.get(temp_key) == nullptr){
                    std::cout << YELLOW << temp_key << " is empty" << NORMAL << std::endl;
                }else if(this->peternakan.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_hewan]){
                    std::cout << YELLOW << temp_key << " doesn't contain " << mapIdxKode[nomor_hewan] << "." << NORMAL << std::endl;
                }else if(!this->peternakan.get(temp_key)->isReadyToHarvest()){
                    std::cout << YELLOW << mapIdxKode[nomor_hewan] << " in " << temp_key << " is not ready yet.\n" << NORMAL << std::endl;
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
            for(Produk* produk : produkHasil){
                this->inventory.addItem(produk);
            }
            this->peternakan.setNull(key);
        }

        std::cout << GREEN << jumlah_petak << " petak hewan " << mapIdxKode[nomor_hewan] << " pada petak " << str_key << " telah dipanen." << NORMAL << std::endl;
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
            string input;
            std::cout << "Barang ingin dibeli: ";
            cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            nomorBarang = std::stoi(input);
            if(mapIdxKode.find(nomorBarang) == mapIdxKode.end() || nomorBarang <= 0){
                std::cout << "Nomor barang is invalid!\n" << std::endl;
            }else if(Toko::catalogPrice[mapIdxKode[nomorBarang]] > this->uang){
                std::cout << YELLOW << "Barang is too expensive!\n" << NORMAL << std::endl;
            }else{
                validNomorBarang = true;
            }
        }

        int kuantitas;
        Asset* barang;
        bool validKuantitas = false;
        bool kuantitasCukup;
        while(!validKuantitas){
            kuantitas = 0;
            kuantitasCukup = false;
            barang = nullptr;
            string input;
            std::cout << "Kuantitas: ";
            cin >> input;

            bool isNumeric = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                std::cout << YELLOW << "Input is not a valid number!\n" << NORMAL << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            kuantitas = std::stoi(input);
            if(kuantitas <= 0){
                std::cout << "Kuantitas is invalid!\n" << std::endl;
            }else if(kuantitas > this->inventory.countAvailableCapacity()){
                cout << YELLOW << "Inventory capacity is not enough\n" << NORMAL << endl;
            }else{
                if(mapType[mapIdxKode[nomorBarang]] == "BANGUNAN"){
                    if(kuantitas > Toko::catalogBangunan[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!\n" << NORMAL << std::endl;
                    }else{
                        barang = Bangunan::resepBangunan[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_MATERIAL_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << mapIdxKode[nomorBarang] << "!\n" << NORMAL << std::endl;
                    }else{
                        barang = ProductMaterial::configProdukMaterial[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_FRUIT_PLANT"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]]->getNamaAsset() << "!\n" << NORMAL << std::endl;
                    }else{
                        barang = ProductFruit::configProdukFruit[mapIdxKode[nomorBarang]];
                        kuantitasCukup = true;
                    }
                }else if(mapType[mapIdxKode[nomorBarang]] == "PRODUCT_ANIMAL"){
                    if(kuantitas > Toko::catalogProduk[mapIdxKode[nomorBarang]]){
                        std::cout << YELLOW << "There isn't enough stock of " << ProductHewan::configProdukHewan[mapIdxKode[nomorBarang]]->getNamaAsset() << "!\n" << NORMAL << std::endl;
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
                    std::cout << GREEN << "Selamat! Anda berhasil membeli " << kuantitas << " " << barang->getNamaAsset() << NORMAL << std::endl;
                    validKuantitas = true;
                }else{
                    std::cout << YELLOW << "You don't have enough money to buy that much!\n" << NORMAL << std::endl;
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
            petakBeli.clear();

            petakBeliInput = "";
            cin.get();
            std::cout << "Petak slot : ";
            getline(cin, petakBeliInput);
            petakBeli = Pemain::stringToArrayComma(petakBeliInput);

            if (petakBeli.size() == kuantitas){
                for (string petak : petakBeli){
                    if (!this->inventory.isValidKey(petak)) {
                        invalidPetakFound = true;
                        std::cout << YELLOW << petak << " is invalid" << std::endl;
                        std::cout << "Press any key to continue..." << NORMAL << endl;
                    }else if(this->inventory.get(petak) != nullptr){
                        invalidPetakFound = true;
                        std::cout << YELLOW << petak << " is not available" << std::endl;
                        std::cout << "Press any key to continue..." << NORMAL << endl;
                    }
                }
            }else{
                invalidPetakFound = true;
                std::cout << YELLOW << "You are trying to buy " << kuantitas << " assets, but input " << petakBeli.size() << " slots" << endl;
                std::cout << "Please input " << kuantitas << " slots" << endl;
                std::cout << "Press any key to continue..." << NORMAL << endl;
            }
        }

        for(const string& petak : petakBeli){
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
