#ifndef PEMAIN_HPP
#define PEMAIN_HPP
#include <string>
#include "Grid.hpp"

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
  void addToInventory(Asset* item, string loc);

  string getStatus() const;
  string getUsername() const;
  int getUang() const ;
  int getBeratBadan() const;
  Inventory getInventory();
  Asset* getFromInventory(string key);
  Asset* getFromInventory(size_t i, size_t j);
  void removeFromInventory(string key);
  int availableInventory();

  void printInventory();
  void makan();
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
  Petani& operator=(const Pemain* other);

  void setStatus();
  void setPetaniID(int petaniID);
  int getPetaniID();
  Ladang getLadang();
  Tumbuhan* getFromLadang(string key);
  void addToLadang(Tumbuhan* tumbuhan, string loc);

  void tanamTanaman();
  void panenTanaman();
  void beliBangunan();

  void printLadang();
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
  Walikota& operator=(const Pemain* other);

  void setStatus();
  void setWalikotaID(int walikotaID);
  int getWalikotaID();

  void tagihPajak();
  void bangunBangunan();
  void tambahAkun();
  void jualBangunan();

  int getNetWorth();
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
  Peternak& operator=(const Pemain* other);

  void setStatus();
  void setPeternakID(int peternakID);
  int getPeternakID();
  Peternakan getPeternakan();
  Hewan* getFromPeternakan(string key);
  void addToPeternakan(Hewan* hewan, string loc);

  void taruhHewan();
  void beriMakan();
  void panenHewan();
  void beliBangunan();

  void printPeternakan();
  int getNetWorth();
  int countPajak();
};

#endif