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

  ~Pemain();

  virtual void setStatus() = 0;
  void setUsername(string username);
  void setUang(int uang);
  void setberatBadan(int beratBadan);
  string getStatus();
  string getUsername() const;
  int getUang();
  int getBeratBadan();

  // virtual void countPajak() = 0;
};

class Petani : public Pemain{
private:
  int petaniID;
  //static map<Tumbuhan> ladang;
public:
  Petani();
  Petani(string username, int uang, int beratBadan);
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

  // void countPajak();
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
  void setWalikotaID();
  int getWalikotaID();

  void tagihPajak();
  void bangunBangunan();
  void tambahAkun();
  void jualBangunan();

  // void countPajak();
};

class Peternak : public Pemain{
private:
  int peternakID;
  //static map<Hewan> peternakan;
public:
  Peternak();
  Peternak(string username, int uang, int beratBadan);
  ~Peternak();
  Peternak(Peternak& other);
  Peternak& operator=(const Peternak& other);

  void setStatus();
  void setPeternakID();
  //void setLadang();
  int getPeternakID();
  //map<Hewan> getPeternakan();
  //void printPeternakan();

  void taruhHewan();
  void beriMakan();
  void panenHewan();
  void beliBangunan();
  // void countPajak();
};
#endif