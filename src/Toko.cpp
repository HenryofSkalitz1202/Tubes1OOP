#include "Toko.hpp"
#include "Exception.hpp"

Toko::Toko() {
    for (auto const& x: Bangunan::resepBangunan) {
        this->listJumlahAsset[x.first] = 0;
    }
    for (auto const& x: Produk::configProduk) {
        this->listJumlahAsset[x.first] = 0;
    }
    for (auto const& x: Hewan::configHewan) {
        this->listAssetTersedia.push_back(x.second);
    }
    for (auto const& x: Tumbuhan::configTumbuhan) {
        this->listAssetTersedia.push_back(x.second);
    }
    this->jumlahBangunan = 0;
    this->jumlahProduk = 0;
}

Toko::~Toko() {}

Asset* Toko::beli(int pilihan, int jumlah, int& uang) {
    try {
        if (pilihan > this->listAssetTersedia.size() || pilihan < 1) {
            throw InvalidPilihanBeliException();
        }
        string assetName = this->listAssetTersedia[pilihan-1]->getNamaAsset();
        int cost = jumlah*getAsset(assetName)->getPrice();
        if (cost > uang) {
            throw NotEnoughMoneyException();
        }
        uang -= cost;
        setJumlah(assetName, getJumlah(assetName) - jumlah);
        return getAsset(assetName);
    } catch(InvalidJumlahAssetTokoException& e) {
        cout << "Jumlah barang yang ingin dibeli tidak sesuai." << endl;
    } catch(InvalidPilihanBeliException& e) {
        cout << e.what() << endl;
    } catch(NotEnoughMoneyException& e) {
        cout << e.what() << endl;
    }
}

int Toko::jual(vector<Asset*> listItem) {
    int totalHarga = 0;
    for (auto const& item: listItem) {
        setJumlah(item->getNamaAsset(), getJumlah(item->getNamaAsset()) + 1);
        totalHarga += item->getPrice();
    }
    return totalHarga;
}

Asset* Toko::getAsset(string assetName) {
    if (Bangunan::resepBangunan.count(assetName) != 0) {
        return Bangunan::resepBangunan[assetName];
    } else if (Produk::configProduk.count(assetName) != 0) {
        return Produk::configProduk[assetName];
    } else if (Hewan::configHewan.count(assetName) != 0) {
        return Hewan::configHewan[assetName];
    } else if (Tumbuhan::configTumbuhan.count(assetName) != 0) {
        return Tumbuhan::configTumbuhan[assetName];
    }
}

void Toko::setJumlah(string name, int n) {
    if (n < 0) {
        throw InvalidJumlahAssetTokoException();
    }
    if (getAsset(name)->getAssetType() == "BANGUNAN" || getAsset(name)->getAssetType() == "PRODUK") {
        if (this->listJumlahAsset[name] == 0 && n > 0) {
            addTersedia(getAsset(name));
        }
        if (this->listJumlahAsset[name] > 0 && n == 0) {
            removeTersedia(getAsset(name));
        }
        this->listJumlahAsset[name] = n;
    }
}

void Toko::addTersedia(Asset* asset) {
    if (asset->getAssetType() == "BANGUNAN") {
        this->listAssetTersedia.insert(this->listAssetTersedia.begin() + this->jumlahBangunan, asset);
        this->jumlahBangunan++;
    }
    if (asset->getAssetType() == "PRODUK") {
        this->listAssetTersedia.insert(this->listAssetTersedia.begin() + this->jumlahBangunan + this->jumlahProduk, asset);
        this->jumlahProduk++;
    }
}

void Toko::removeTersedia(Asset* asset) {
    int id = 0;
    for (auto a : this->listAssetTersedia) {
        if (asset->getNamaAsset() == a->getNamaAsset()) {
            break;
        }
        id++;
    }
    this->listAssetTersedia.erase(this->listAssetTersedia.begin() + id);
    if (asset->getAssetType() == "BANGUNAN") {
        this->jumlahBangunan--;
    }
    if (asset->getAssetType() == "PRODUK") {
        this->jumlahProduk--;
    }
}

int Toko::getJumlahBangunan() const {
    return this->jumlahBangunan;
}

int Toko::getJumlahProduk() const {
    return this->jumlahProduk;
}

int Toko::getJumlah(string name) {
    return this->listJumlahAsset[name];
}

void Toko::displayToko() {
    cout << "Selamat datang di toko!!" << endl;
    cout << "Berikut merupakan hal yang dapat Anda Beli" << endl;
    int n = this->listAssetTersedia.size();
    for (int i=0; i<n; i++) {
        cout << i+1 << ". " << this->listAssetTersedia[i]->getNamaAsset() << " - [Harga: " << this->listAssetTersedia[i]->getPrice();
        if (i < this->jumlahBangunan + this->jumlahProduk) {
            cout << ", Tersedia: " << getJumlah(this->listAssetTersedia[i]->getNamaAsset()) << "]" << endl;
        } else {
            cout << "]" << endl;
        }
    }
}