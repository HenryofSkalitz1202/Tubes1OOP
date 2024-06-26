#ifndef PEMAIN_HPP
#define PEMAIN_HPP
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "Toko.cpp"
#include "Grid.cpp"

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

  static vector<string> stringToArrayComma(const string& input);

  ~Pemain();

  void setUsername(string username);
  void setUang(int uang);
  void setberatBadan(int beratBadan);
  void addToInventory(Asset* item);

  string getUsername();
  int getUang();
  int getBeratBadan();
  string getStatus();
  Inventory getInventory();
  Asset* getFromInventory(string key);

  void printInventory();
  void jualAsset();
  void makan();
  //void simpan();

  virtual void beliAsset(Toko* store) = 0;
  virtual int getNetWorth() = 0;
  virtual int countPajak() = 0;
};

class Petani : public Pemain{
private:
  int petaniID;
  Ladang ladang;
  const int ktkp = 13;
public:
  Petani(int petaniID, string username);
  Petani(int petaniID, string username, int uang, int beratBadan);
  ~Petani();
  Petani(Petani& other);
  Petani& operator=(const Petani& other);

  void setPetaniID(int petaniID);
  int getPetaniID();
  Ladang getLadang();
  Tumbuhan* getFromLadang(string key);
  void addToLadang(Tumbuhan* tumbuhan, string loc);

  void printLadang();
  void tanamTanaman();
  void panenTanaman();
  void beliAsset(Toko* store);

  int getNetWorth();
  int countPajak();
};

class Walikota : public Pemain{
private:
  int walikotaID;

public:
  Walikota(int walikotaID, string username);
  Walikota(int walikotaID, string username, int uang, int beratBadan);
  ~Walikota();
  Walikota(Walikota& other);
  Walikota& operator=(const Walikota& other);

  void setWalikotaID(int walikotaID);
  int getWalikotaID();

  void bangunBangunan();
  Pemain* tambahAkun(vector<Pemain*> players);
  void beliAsset(Toko* store);

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
  Peternak(int peternakID, string username);
  Peternak(int peternakID, string username, int uang, int beratBadan);
  ~Peternak();
  Peternak(Peternak& other);
  Peternak& operator=(const Peternak& other);

  void setPeternakID(int peternakID);
  int getPeternakID();
  Peternakan getPeternakan();
  Hewan* getFromPeternakan(string key);
  void addToPeternakan(Hewan* hewan, string loc);

  void printPeternakan();
  void taruhHewan();
  void beriMakan();
  void panenHewan();
  void beliAsset(Toko* store);

  int getNetWorth();
  int countPajak();
};

#endif