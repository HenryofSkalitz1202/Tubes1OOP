#ifndef PEMAIN_HPP
#define PEMAIN_HPP
#include <string>

using namespace std;

class Pemain{
protected:
  string username;
  int uang;
  int beratBadan;
  string status;
  //static map<Barang> inventory;
public:
  static int beratWin;
  static int uangWin;
  static int defaultBerat;
  static int defaultUang;

  virtual void setStatus() = 0;
  void setUang();
  void setString();
  void setberatBadan();
  string getStatus();
  string getUsername();
  int getUang();
  int getBeratBadan();
};

class Petani : public Pemain{
private:
  int petaniID;
  //static map<Tumbuhan> ladang;
public:
  Petani();
  Petani(string username);
  ~Petani();
  Petani(Petani& other);
  Petani& operator=(const Petani& other);

  void setStatus();
  void setPetaniID();
  //void setLadang();
  int getPetaniID();
  //map<Tumbuhan> getLadang();

  void tanamTanaman();
  void panenTanaman();
  void beliBangunan();
};

class Walikota : public Pemain{
private:
  int walikotaID;

public:
  Walikota();
  Walikota(string username);
  ~Walikota();
  Walikota(Walikota& other);
  Walikota& operator=(const Walikota& other);

  void setStatus();
  void setWalikotaID();
  string getWalikotaID();

  void tagihPajak();
  void bangunBangunan();
  void tambahAkun();
  void jualBangunan();
};

class Peternak : public Pemain{
private:
  int peternakID;
  //static map<Hewan> peternakan;
public:
  Peternak();
  Peternak(string username);
  ~Peternak();
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
#endif