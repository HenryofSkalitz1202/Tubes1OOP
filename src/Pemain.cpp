#include "Pemain.hpp"

int Pemain::uangWin;
int Pemain::beratWin;
//<---------------PEMAIN----------------->
// vector<string> Pemain::stringToArrayComma(const string& input) {
//     // Define the lambda function here
//     auto isspace = [](int ch) {
//         return !std::isspace(ch);
//     };

//     std::vector<std::string> result;
//     std::istringstream iss(input);
//     std::string token;
//     while (std::getline(iss, token, ',')) {
//         token.erase(token.begin(), std::find_if(token.begin(), token.end(), isspace));
//         token.erase(std::find_if(token.rbegin(), token.rend(), isspace).base(), token.end());
//         result.push_back(token);
//     }
//     return result;
// }

Pemain::Pemain(){}

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

void Pemain::jualAsset(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        cout << "Berikut merupakan penyimpanan Anda" << endl;
        this->inventory.print();

        bool invalidPetakFound = true;
        vector<string> petakJual;
        string petakJualInput;
        while (invalidPetakFound) {
            invalidPetakFound = false;

            petakJualInput = "";
            cout << "\nSilahkan pilih petak yang ingin Anda jual!\nPetak : " << endl;
            cin >> petakJualInput;
            petakJual = Pemain::stringToArrayComma(petakJualInput);

            for (const std::string& petak : petakJual) {
                if (!this->inventory.isValidKey(petak)) {
                    invalidPetakFound = true; // Set the flag if an invalid petak is found
                    cout << petak << " is invalid" << endl;
                }else if(this->inventory.get(petak) == nullptr){
                    invalidPetakFound = true;
                    cout << petak << " is empty" << endl;
                }
            }
        }

        for(const string& petak : petakJual){
            Asset* assetptr = this->inventory.get(petak);
            if(dynamic_cast<Hewan*>(assetptr) || dynamic_cast<Tumbuhan*>(assetptr)){
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<Bangunan*>(assetptr) || dynamic_cast<ProductMaterial*>(assetptr)){
                Toko::catalog[assetptr->getNamaAsset()]++;
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }else if(dynamic_cast<ProductFruit*>(assetptr) || dynamic_cast<ProductHewan*>(assetptr)){
                Toko::catalog[assetptr->getKodeHuruf()]++;
                this->uang += assetptr->getPrice();
                this->inventory.setNull(petak);
            }
        }
    }catch(inventoryEmptyException& e){
        cout << e.what();
    }
}

//<---------------PETANI----------------->
Petani::Petani(){
    this->username = "Petani";
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
}

Petani::Petani(string username, int uang, int beratBadan){
    this->username = username;
    this->uang = uang;
    this->beratBadan = beratBadan;
}

Petani::~Petani(){
    //delete[] ladang;
    //~Pemain();
}

Petani::Petani(Petani& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
}

Petani& Petani::operator=(const Petani& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
}

void Petani::setPetaniID(int petaniID){
    this->petaniID = petaniID;
}

int Petani::getPetaniID(){
    return this->petaniID;
}

void Petani::tanamTanaman(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();

        if(this->inventory.getJumlahTumbuhan()){
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
                cout << key_inv << " is invalid" << endl;
            }else if(this->getFromInventory(key_inv) == nullptr){
                cout << key_inv << " is empty" << endl;
            }else if(!dynamic_cast<Tumbuhan*>(this->getFromInventory(key_inv))){
                cout << "Object in " << key_inv << " is not of Tumbuhan type" << endl;
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
                cout << key_ladang << " is invalid" << endl;
            }else if(this->ladang.get(key_ladang) != nullptr){
                cout << key_ladang << " is not vacant" << endl;
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
                cout << "Nomor tanaman is invalid!\n" << endl;
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
                cout << "Jumlah petak is invalid!\n";
            }else if(jumlah_petak > rekapLadang[mapIdxKode[nomor_tanaman]]){
                cout << "You are trying to harvest more than the amount of petak that is currently available to harvest!\n";
            }else if(this->inventory.countAvailableCapacity() < jumlah_petak){
                cout << "Available inventory capacity is not enough!\n";
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
                    cout << temp_key << " is invalid" << endl;
                }else if(this->ladang.get(temp_key) == nullptr){
                    cout << temp_key << " is empty" << endl;
                }else if(this->ladang.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_tanaman]){
                    cout << temp_key << " doesn't contain " << mapIdxKode[nomor_tanaman] << "." << endl;
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
    cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda beli";

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
Walikota::Walikota(){
    this->username = "Walikota";
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
}

Walikota::Walikota(string username, int uang, int beratBadan){
    this->username = username;
    this->uang = uang;
    this->beratBadan = beratBadan;
}

Walikota::~Walikota(){
    //~Pemain();
}

Walikota::Walikota(Walikota& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
}
  
Walikota& Walikota::operator=(const Walikota& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
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
        cout << "\nBangunan yang ingin dibangun: ";
        cin >> namaBangunan;

        if(Bangunan::resepBangunan.find(namaBangunan) == Bangunan::resepBangunan.end()){
            cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
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
        cout << new_building->getNamaAsset() << " berhasil dibangun dan telah menjadi hak milik walikota!";
    }else{
        cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
        bool first = true;
        for (const auto& pair : materialKurang) {
            if (!first) {
                cout << ", ";
            }
            cout << pair.second << " " << pair.first;
            first = false;
        }
        cout << endl;
    }
}

void Walikota::tambahAkun(vector<Pemain*> players){
    if(this->uang < 50){
        throw uangInsufficientException();
    }  

    string jenis_pemain;
    cout << "Masukkan jenis pemain: ";
    cin >> jenis_pemain;

    string nama_pemain;
    cout << "Masukkan nama pemain: ";
    cin >> nama_pemain;

    cout << "Pemain baru ditambahkan!\nSelamat datang \"" << nama_pemain << "\" di kota ini!" << endl;
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
Peternak::Peternak(){
    this->username = "Peternak";
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
}

Peternak::Peternak(string username, int uang, int beratBadan){
    this->username = username;
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
}

Peternak::~Peternak(){
    //delete[] peternakan;
    //~Pemain();
}

Peternak::Peternak(Peternak& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
}

Peternak& Peternak::operator=(const Peternak& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
}

void Peternak::setPeternakID(int peternakID){
    this->peternakID = peternakID;
}

int Peternak::getPeternakID(){
    return this->peternakID;
}

void Peternak::taruhHewan(){
    try{
        if(this->inventory.isEmpty()){
            throw inventoryEmptyException();
        }

        this->inventory.rekapInventory();

        if(this->inventory.getJumlahHewan()){
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
                cout << key_inv << " is invalid" << endl;
            }else if(this->getFromInventory(key_inv) == nullptr){
                cout << key_inv << " is empty" << endl;
            }else if(!dynamic_cast<Hewan*>(this->getFromInventory(key_inv))){
                cout << "Object in " << key_inv << "is not of Hewan type" << endl;
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
                cout << key_peternakan << " is invalid" << endl;
            }else if(this->peternakan.get(key_peternakan) != nullptr){
                cout << key_peternakan << " is not vacant" << endl;
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
                cout << key_peternakan << " is invalid" << endl;
            }else if(this->peternakan.get(key_peternakan) == nullptr){
                cout << key_peternakan << " is empty";
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
                cout << slot << " is invalid" << endl;
            }else if(this->getFromInventory(slot) == nullptr){
                cout << slot << " is empty" << endl;
            }else if(!dynamic_cast<ProductFruit*>(this->getFromInventory(slot)) && !dynamic_cast<ProductHewan*>(this->getFromInventory(slot))){
                cout << this->getFromInventory(slot)->getNamaAsset() << " is inedible" << endl;
            }else if(dynamic_cast<ProductFruit*>(this->getFromInventory(slot)) && dynamic_cast<Carnivore*>(this->peternakan.get(key_peternakan))){
                cout << "You are feeding " << this->getFromInventory(slot)->getNamaAsset() << " to "<< this->peternakan.get(key_peternakan) << ". Carnivore can't eat ProductFruit." << endl;
            }else if(dynamic_cast<ProductHewan*>(this->getFromInventory(slot)) && dynamic_cast<Herbivore*>(this->peternakan.get(key_peternakan))){
                cout << "You are feeding " << this->getFromInventory(slot)->getNamaAsset() << " to "<< this->peternakan.get(key_peternakan) << ". Herbivore can't eat ProductHewan." << endl;
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
                cout << "Nomor hewan is invalid!\n" << endl;
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
                cout << "Jumlah petak is invalid!\n";
            }else if(jumlah_petak > rekapPeternakan[mapIdxKode[nomor_hewan]]){
                cout << "You are trying to harvest more than the amount of petak that is currently available to harvest!\n";
            }else if(this->inventory.countAvailableCapacity() < jumlah_petak){
                cout << "Available inventory capacity is not enough!\n";
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
                    cout << temp_key << " is invalid" << endl;
                }else if(this->peternakan.get(temp_key) == nullptr){
                    cout << temp_key << " is empty" << endl;
                }else if(this->peternakan.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_hewan]){
                    cout << temp_key << " doesn't contain " << mapIdxKode[nomor_hewan] << "." << endl;
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

void Peternak::beliBangunan(){
    //TO DO
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
