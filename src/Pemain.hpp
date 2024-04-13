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
  Inventory inventory;
public:
  static int beratWin;
  static int uangWin;
  static int defaultBerat;
  static int defaultUang;

  static vector<string> stringToArrayComma(const string& input){
    auto isspace = [](int ch) {
        return !std::isspace(ch);
    };

    std::vector<std::string> result;
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, ',')) {
        token.erase(token.begin(), std::find_if(token.begin(), token.end(), isspace));
        token.erase(std::find_if(token.rbegin(), token.rend(), isspace).base(), token.end());
        result.push_back(token);
    }
    return result;
  }

  Pemain();
  ~Pemain();

  void setUsername(string username);
  void setUang(int uang);
  void setberatBadan(int beratBadan);
  void addToInventory(Asset* item);

  string getUsername();
  int getUang();
  int getBeratBadan();
  Asset* getFromInventory(string key);

  void jualAsset();

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

  void setPetaniID(int petaniID);
  int getPetaniID();

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
  Walikota();
  Walikota(string username, int uang, int beratBadan);
  ~Walikota();
  Walikota(Walikota& other);
  Walikota& operator=(const Walikota& other);

  void setWalikotaID(int walikotaID);
  int getWalikotaID();

  void bangunBangunan();
  void tambahAkun(vector<Pemain*> players);

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