#include "Pemain.hpp"

int Pemain::uangWin;
int Pemain::beratWin;
//<---------------PEMAIN----------------->
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

string Pemain::getStatus(){
    return this->status;
}

string Pemain::getUsername() const{
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

void Pemain::printInventory() {
    this->inventory.print();
}
//<---------------PETANI----------------->
Petani::Petani(){
    this->username = "Petani";
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
    this->status = "petani";
}

Petani::Petani(string username, int uang, int beratBadan){
    this->username = username;
    this->uang = uang;
    this->beratBadan = beratBadan;
    this->status = "petani";
}

Petani::~Petani(){
    //delete[] ladang;
    //~Pemain();
}

Petani::Petani(Petani& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->status = other.status;
}

Petani& Petani::operator=(const Petani& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->status = other.status;
}

void Petani::setStatus(){
    this->status = "petani";
}

void Petani::setPetaniID(int petaniID){
    this->petaniID = petaniID;
}

  //void setLadang();
int Petani::getPetaniID(){
    return this->petaniID;
}
  //map<Tumbuhan> getLadang();

void Petani::tanamTanaman(){
    std::cout << "Pilih tanaman dari penyimpanan" << std::endl;
    this->inventory.print();

    string key_inv;
    std::cout << "Slot : ";
    std::cin >> key_inv;

    Tumbuhan* tumbuhan = dynamic_cast<Tumbuhan*>(this->getFromInventory(key_inv));

    try{
        if(tumbuhan){
            std::cout << "Kamu memilih " << tumbuhan->getNamaAsset() << std::endl;
            std::cout << "\n";
            std::cout << "Pilih petak yang akan ditanami" << std::endl;
            this->ladang.print();

            string key_ladang;
            std::cout << "Petak tanah: ";
            std::cin >> key_ladang;

            this->ladang.setWithKey(key_ladang, tumbuhan);

            std::cout << "\nCangkul, cangkul, cangkul yang dalam~!" << std::endl;
            std::cout << tumbuhan->getNamaAsset() << " berhasil ditanam!";

            this->inventory.setNull(key_inv);
            delete tumbuhan;
        }else{
            std::cout << "An attempt is detected to plant " << this->getFromInventory(key_inv)->getNamaAsset() << " which is of " << this->getFromInventory(key_inv)->getAssetType() << " type.";
            throw tanamNotTumbuhanException();
        }
    }catch(tanamNotTumbuhanException& e){
        std::cout << e.what();
    }catch(insertIntoUnemptyCellException& e){
        std::cout << e.what();
    }catch(outOfBoundsException& e){
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

        int nomor_tanaman = 0;
        int jumlah_petak = 0;

        std::cout << "Nomor tanaman yang ingin dipanen: ";
        std::cin >> nomor_tanaman;

        if(mapIdxKode.find(nomor_tanaman) == mapIdxKode.end()){
            throw invalidNomorTanamanException();
        }
        
        std::cout << "\nJumlah petak yang ingin dipanen: ";
        std::cin >> jumlah_petak;

        if(jumlah_petak > rekapLadang[mapIdxKode[nomor_tanaman]] || jumlah_petak <= 0){
            throw invalidJumlahPetakException();
        }

        std::cout << "\nPilih petak yang ingin dipanen:" << std::endl;
        string str_key = "";
        vector<string> key_vec;

        for(int i = 1; i <= jumlah_petak; i++){
            string temp_key = "";
            std::cout << "Petak ke-" << i << ": ";
            std::cin >> temp_key;

            if(this->ladang.isValidKey(temp_key)){
                key_vec.push_back(temp_key);
            }else{
                throw invalidKeyException();
            }

            if(this->ladang.get(temp_key) == nullptr){
                std::cout << "Petak " << temp_key << " is still vacant. ";
                throw invalidPetakException();
            } else if(this->ladang.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_tanaman]){
                std::cout << "Petak " << temp_key << " doesn't contain hewan " << mapIdxKode[nomor_tanaman] << ". ";
                throw invalidPetakException();
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
    }catch(invalidNomorTanamanException& e){
        std::cout << e.what();
    }catch(invalidJumlahPetakException& e){
        std::cout << e.what();
    }catch(invalidKeyException& e){
        std::cout << e.what();
    }catch(invalidPetakException& e){
        std::cout << e.what();
    }
}

void Petani::beliBangunan(){
    //TO DO
}

void Petani::printLadang() {
    this->inventory.print();
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
    this->status = "walikota";
}

Walikota::Walikota(string username, int uang, int beratBadan){
    this->username = username;
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
    this->status = "walikota";
}

Walikota::~Walikota(){
    //~Pemain();
}

Walikota::Walikota(Walikota& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->status = other.status;
}
  
Walikota& Walikota::operator=(const Walikota& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->status = other.status;
}

void Walikota::setStatus(){
    this->status = "walikota";
}

void Walikota::setWalikotaID(int walikotaID){
    this->walikotaID = walikotaID;
}

int Walikota::getWalikotaID(){
    return this->walikotaID;
}

void Walikota::tagihPajak(){
    //TO DO
}
  
void Walikota::bangunBangunan(){
    //TO DO
}

void Walikota::tambahAkun(){
    //TO DO
}

void Walikota::jualBangunan(){
    //TO DO
}

int Walikota::getNetWorth(){
    return this->inventory.getTotalWorth() + this->uang;
}

int Walikota::countPajak(){
    //TO DO
}

//<---------------PETERNAK----------------->
Peternak::Peternak(){
    this->username = "Peternak";
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
    this->status = "peternak";
}

Peternak::Peternak(string username, int uang, int beratBadan){
    this->username = username;
    this->uang = defaultUang;
    this->beratBadan = defaultBerat;
    this->status = "walikota";
}

Peternak::~Peternak(){
    //delete[] peternakan;
    //~Pemain();
}

Peternak::Peternak(Peternak& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->status = other.status;
}

Peternak& Peternak::operator=(const Peternak& other){
    this->username = other.username;
    this->uang = other.uang;
    this->beratBadan = other.beratBadan;
    this->status = other.status;
}

void Peternak::setStatus(){
    this->status = "peternak";
}

void Peternak::setPeternakID(int peternakID){
    this->peternakID = peternakID;
}

int Peternak::getPeternakID(){
    return this->peternakID;
}

void Peternak::taruhHewan(){
    std::cout << "Pilih hewan dari penyimpanan" << std::endl;
    this->inventory.print();

    string key_inv;
    std::cout << "Slot : ";
    std::cin >> key_inv;

    Hewan* hewan = dynamic_cast<Hewan*>(this->getFromInventory(key_inv));

    try{
        if(hewan){
            std::cout << "Kamu memilih " << hewan->getNamaAsset() << std::endl;
            std::cout << "\nPilih petak peternakan yang akan ditinggali" << std::endl;
            this->peternakan.print();

            string key_peternakan;
            std::cout << "Petak peternakan: ";
            std::cin >> key_peternakan;

            this->peternakan.setWithKey(key_peternakan, hewan);

            std::cout << "\nDengan hati-hati, kamu meletakkan seekor " << hewan->getNamaAsset() << " di kandang." << std::endl;
            std::cout << hewan->getNamaAsset() << " telah menjadi peliharaanmu sekarang!";

            this->inventory.setNull(key_inv);
        }else{
            std::cout << "An attempt is detected to raise " << this->getFromInventory(key_inv)->getNamaAsset() << " which is of " << this->getFromInventory(key_inv)->getAssetType() << " type.";
            throw ternakNotHewanException();
        }
    }catch(ternakNotHewanException& e){
        std::cout << e.what();
    }catch(insertIntoUnemptyCellException& e){
        std::cout << e.what();
    }catch(outOfBoundsException& e){
        std::cout << e.what();
    }
}

void Peternak::beriMakan(){
    std::cout << "Pilih petak kandang yang akan diberi makan" << std::endl;
    this->peternakan.print();

    string key_peternakan;
    std::cout << "Petak peternakan: ";
    std::cin >> key_peternakan;

    try{
        if(!this->peternakan.isValidKey(key_peternakan)){
            throw invalidKeyException();
        }else if(this->peternakan.get(key_peternakan) == nullptr){
            std::cout << "Petak " << key_peternakan << " is still vacant. ";
            throw invalidPetakException();
        }

        std::cout << "Kamu memilih " << this->peternakan.get(key_peternakan)->getNamaAsset() << " untuk diberi makan." << std::endl;
        std::cout << "Pilih pangan yang akan diberikan" << std::endl;
        this->inventory.print();

        string slot;
        std::cout << "Slot: ";
        std::cin >> slot;

        Produk* pakan = dynamic_cast<Produk*>(this->getFromInventory(slot));
        if(pakan){
            this->peternakan.get(key_peternakan)->makan(pakan);
            std::cout << this->peternakan.get(key_peternakan)->getNamaAsset() << " sudah diberi makan dan beratnya menjadi " << this->peternakan.get(key_peternakan)->getWeight() << "." << std::endl;

            this->inventory.setNull(slot);
        }else{
            cout << "An attempt is detected to feed " << this->peternakan.get(key_peternakan)->getNamaAsset() << " with " << this->inventory.get(slot)->getNamaAsset();
            throw HewanWrongFoodTypeException();
        }
    }catch(invalidKeyException& e){
        std::cout << e.what();
    }catch(invalidPetakException& e){
        std::cout << e.what();
    }catch(HewanWrongFoodTypeException& e){
        cout << e.what();
    }catch(HerbivoreWrongFoodTypeException& e){
        cout << e.what();
    }catch(CarnivoreWrongFoodTypeException& e){
        cout << e.what();
    }catch(OmnivoreWrongFoodTypeException& e){
        cout << e.what();
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

        int nomor_hewan = 0;
        int jumlah_petak = 0;

        std::cout << "Nomor hewan yang ingin dipanen: ";
        std::cin >> nomor_hewan;

        if(mapIdxKode.find(nomor_hewan) == mapIdxKode.end()){
            throw invalidNomorHewanException();
        }
        
        std::cout << "\nJumlah petak yang ingin dipanen: ";
        std::cin >> jumlah_petak;

        if(jumlah_petak > rekapPeternakan[mapIdxKode[nomor_hewan]] || jumlah_petak <= 0){
            throw invalidJumlahPetakException();
        }

        std::cout << "\nPilih petak yang ingin dipanen:" << std::endl;
        string str_key = "";
        vector<string> key_vec;

        for(int i = 1; i <= jumlah_petak; i++){
            string temp_key = "";
            std::cout << "Petak ke-" << i << ": ";
            std::cin >> temp_key;

            if(this->peternakan.isValidKey(temp_key)){
                key_vec.push_back(temp_key);
            }else{
                throw invalidKeyException();
            }

            if(this->peternakan.get(temp_key) == nullptr){
                std::cout << "Petak " << temp_key << " is still vacant. ";
                throw invalidPetakException();
            } else if(this->peternakan.get(temp_key)->getKodeHuruf() != mapIdxKode[nomor_hewan]){
                std::cout << "Petak " << temp_key << " doesn't contain hewan " << mapIdxKode[nomor_hewan] << ". ";
                throw invalidPetakException();
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

        std::cout << jumlah_petak << " petak tanaman " << mapIdxKode[nomor_hewan] << " pada petak " << str_key << " telah dipanen." << std::endl;
    }catch(peternakanEmptyException& e){
        std::cout << e.what();
    }catch(noneSiapPanenPeternakanException& e){
        std::cout << e.what();
    }catch(invalidNomorHewanException& e){
        std::cout << e.what();
    }catch(invalidJumlahPetakException& e){
        std::cout << e.what();
    }catch(invalidKeyException& e){
        std::cout << e.what();
    }catch(invalidPetakException& e){
        std::cout << e.what();
    }
}

void Peternak::beliBangunan(){
    //TO DO
}

void Peternak::printPeternakan() {
    this->inventory.print();
}

int Peternak::getNetWorth(){
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
