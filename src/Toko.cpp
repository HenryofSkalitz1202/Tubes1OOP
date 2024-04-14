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

Asset* Toko::beli(int n, int jumlah) {
    try {
        if (n > this->listAssetTersedia.size() || n < 1) {
            throw InvalidPilihanBeliException();
        }
        Asset* asset = this->listAssetTersedia[n-1];
        setJumlah(asset->getNamaAsset(), this->listJumlahAsset[asset->getNamaAsset()] - jumlah);
        return asset;
    } catch(InvalidJumlahAssetTokoException& e) {
        cout << "Jumlah barang yang ingin dibeli tidak sesuai." << endl;
    }
}

int Toko::jual(Asset* asset, int jumlah) {
    try {
        setJumlah(asset->getNamaAsset(), this->listJumlahAsset[asset->getNamaAsset()] + jumlah);
        return asset->getPrice()*jumlah;
    } catch(InvalidJumlahAssetTokoException& e) {
        cout << "Jumlah barang yang ingin dijual tidak sesuai." << endl;
    }
}

void Toko::setJumlah(string name, int n) {
    if (n < 0) {
        throw InvalidJumlahAssetTokoException();
    }
    if (Bangunan::resepBangunan.count(name) != 0) {
        if (this->listJumlahAsset[name] == 0 && n > 0) {
            addTersedia(Bangunan::resepBangunan[name]);
        }
        if (this->listJumlahAsset[name] > 0 && n == 0) {
            removeTersedia(Bangunan::resepBangunan[name]);
        }
        this->listJumlahAsset[name] = n;
    } else if (Produk::configProduk.count(name) != 0) {
        if (this->listJumlahAsset[name] == 0 && n > 0) {
            addTersedia(Produk::configProduk[name]);
        }
        if (this->listJumlahAsset[name] > 0 && n == 0) {
            removeTersedia(Produk::configProduk[name]);
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
        cout << i+1 << ". " << this->listAssetTersedia[i]->getNamaAsset() << " - " << this->listAssetTersedia[i]->getPrice();
        if (i < this->jumlahBangunan + this->jumlahProduk) {
            cout << " (" << this->listJumlahAsset[this->listAssetTersedia[i]->getNamaAsset()] << ")" << endl;
        } else {
            cout << endl;
        }
    }
}