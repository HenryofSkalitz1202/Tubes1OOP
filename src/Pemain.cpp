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
    cout << "Pilih tanaman dari penyimpanan" << endl;
    this->inventory.print();

    string key_inv;
    cout << "Slot : ";
    cin >> key_inv;

    Tumbuhan* tumbuhan = dynamic_cast<Tumbuhan*>(this->inventory.get(key_inv));

    try{
        if(tumbuhan){
            cout << "Kamu memilih " << tumbuhan->getNamaAsset() << endl;
            cout << "\n";
            cout << "Pilih petak yang akan ditanami" << endl;
            this->ladang.print();

            string key_ladang;
            cout << "Petak tanah: ";
            cin >> key_ladang;

            this->ladang.setWithKey(key_ladang, tumbuhan);

            cout << "\nCangkul, cangkul, cangkul yang dalam~!" << endl;
            cout << tumbuhan->getNamaAsset() << " berhasil ditanam!";

            this->inventory.setNull(key_inv);
            delete tumbuhan;
        }else{
            cout << "An attempt is detected to plant " << this->inventory.get(key_inv)->getNamaAsset() << " which is of " << this->inventory.get(key_inv)->getAssetType() << " type.";
            throw tanamNotTumbuhanException();
        }
    }catch(tanamNotTumbuhanException& e){
        cout << e.what();
    }catch(insertIntoUnemptyCellException& e){
        cout << e.what();
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
            cout << "- " << pair.first << ": " << Tumbuhan::configTumbuhan[pair.first]->getNamaAsset() << endl;
        }

        cout << "\nPilih tanaman siap panen yang kamu miliki" << endl;
        int idx = 0;
        for(const auto& pair : rekapLadang){
            if(pair.second > 0){
                cout << ++idx << ". " << pair.first << " (" << pair.second << " petak siap panen)" << endl;
            }
        }
    }catch(ladangEmptyException& e){
        cout << e.what();
    }catch(noneSiapPanenLadangException& e){
        cout << e.what();
    }
}

void Petani::beliBangunan(){
    //TO DO
}

void Petani::countPajak(){
    //TO DO
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
//void Walikota::setWalikotaID();
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

void Walikota::countPajak(){
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
//void Peternak::setLadang();
int Peternak::getPeternakID(){
    return this->peternakID;
}
//map<Tumbuhan> getLadang();

void Peternak::taruhHewan(){
    cout << "Pilih hewan dari penyimpanan" << endl;
    this->inventory.print();

    string key_inv;
    cout << "Slot : ";
    cin >> key_inv;

    Hewan* hewan = dynamic_cast<Hewan*>(this->inventory.get(key_inv));

    try{
        if(hewan){
            cout << "Kamu memilih " << hewan->getNamaAsset() << endl;
            cout << "\nPilih petak peternakan yang akan ditinggali" << endl;
            this->peternakan.print();

            string key_peternakan;
            cout << "Petak peternakan: ";
            cin >> key_peternakan;

            this->peternakan.setWithKey(key_peternakan, hewan);

            cout << "\nDengan hati-hati, kamu meletakkan seekor " << hewan->getNamaAsset() << " di kandang." << endl;
            cout << hewan->getNamaAsset() << " telah menjadi peliharaanmu sekarang!";

            this->inventory.setNull(key_inv);
        }else{
            cout << "An attempt is detected to raise " << this->inventory.get(key_inv)->getNamaAsset() << " which is of " << this->inventory.get(key_inv)->getAssetType() << " type.";
            throw ternakNotHewanException();
        }
    }catch(ternakNotHewanException& e){
        cout << e.what();
    }catch(insertIntoUnemptyCellException& e){
        cout << e.what();
    }catch(outOfBoundsException& e){
        std::cout << e.what();
    }
}

void Peternak::beriMakan(){
    //TO DO
}
  
void Peternak::panenHewan(){
    //TO DO
}

void Peternak::beliBangunan(){
    //TO DO
}

void Peternak::countPajak(){
    //TO DO
}
