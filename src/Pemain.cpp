#include "Pemain.hpp"

//<---------------PEMAIN----------------->
Pemain::~Pemain(){
    //delete[] inventory;
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
  
// void Petani::setPetaniID(){
//     this.petaniID = 
//}

  //void setLadang();
int Petani::getPetaniID(){
    return this->petaniID;
}
  //map<Tumbuhan> getLadang();

void Petani::tanamTanaman(){
    //TO DO
}

void Petani::panenTanaman(){
    //TO DO
}

void Petani::beliBangunan(){
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

  Peternak(Peternak& other);
  Peternak& operator=(const Peternak& other);

  void setStatus();
  void setPeternakID();
  //void setLadang();
  int getPeternakID();
  //map<Tumbuhan> getLadang();

  void taruhHewan();
  void beriMakan();
  void panenHewan();
  void beliBangunan();
};