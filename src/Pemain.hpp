#ifndef PEMAIN_HPP
#define PEMAIN_HPP
#include <string>
#include "Toko.cpp"

using namespace std;

class Pemain{
protected:
  string username;
  int uang;
  int beratBadan;
  string status;
  Inventory inventory;
public:
  static int beratWin;
  static int uangWin;
  static int defaultBerat;
  static int defaultUang;

  Pemain();
  ~Pemain();

  virtual void setStatus() = 0;
  void setUsername(string username);
  void setUang(int uang);
  void setberatBadan(int beratBadan);
  void addToInventory(Asset* item);

  string getStatus();
  string getUsername();
  int getUang();
  int getBeratBadan();
  Asset* getFromInventory(string key);

  virtual int getNetWorth() = 0;
  virtual int countPajak() = 0;
};

class Petani : public Pemain{
private:
  int petaniID;
  Ladang ladang;
  const int ktkp = 13;
public:
  Petani();
  Petani(string username, int uang, int beratBadan);
  ~Petani();
  Petani(Petani& other);
  Petani& operator=(const Petani& other);

  void setStatus();
  void setPetaniID(int petaniID);
  int getPetaniID();

  void tanamTanaman();
  void panenTanaman();
  void beliBangunan(Toko* store);

  int getNetWorth();
  int countPajak();
};

class Walikota : public Pemain{
private:
  int walikotaID;

public:
  Walikota();
  Walikota(string username, int uang, int beratBadan);
  ~Walikota();
  Walikota(Walikota& other);
  Walikota& operator=(const Walikota& other);

  void setStatus();
  void setWalikotaID(int walikotaID);
  int getWalikotaID();

  void bangunBangunan();
  void tambahAkun(vector<Pemain*> players);
  void jualBangunan();

  int getNetWorth();
  int pungutPajak(vector<Pemain*> players);
  int countPajak();
};

class Peternak : public Pemain{
private:
  int peternakID;
  Peternakan peternakan;
  const int ktkp = 11;
public:
  Peternak();
  Peternak(string username, int uang, int beratBadan);
  ~Peternak();
  Peternak(Peternak& other);
  Peternak& operator=(const Peternak& other);

  void setStatus();
  void setPeternakID(int peternakID);
  int getPeternakID();

  void taruhHewan();
  void beriMakan();
  void panenHewan();
  void beliBangunan();

  int getNetWorth();
  int countPajak();
};

#endif