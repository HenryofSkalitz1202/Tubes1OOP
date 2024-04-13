#include "Toko.hpp"
#include "Exception.hpp"

Toko::Toko() {
    for (auto const& [key,_]: Bangunan::resepBangunan) {
        this->listJumlahAsset[key] = 0;
    }
    for (auto const& [key,_]: Produk::configProduk) {
        this->listJumlahAsset[key] = 0;
    }
    for (auto const& [_,value]: Hewan::configHewan) {
        this->listAssetTersedia.push_back(value);
    }
    for (auto const& [_,value]: Tumbuhan::configTumbuhan) {
        this->listAssetTersedia.push_back(value);
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
        setJumlah(asset, this->listJumlahAsset[asset->getKodeHuruf()] - jumlah);
        return asset;
    } catch(InvalidJumlahAssetTokoException& e) {
        cout << "Jumlah barang yang ingin dibeli tidak sesuai." << endl;
    }
}

int Toko::jual(Asset* asset, int jumlah) {
    try {
        setJumlah(asset, this->listJumlahAsset[asset->getKodeHuruf()] + jumlah);
        return asset->getPrice()*jumlah;
    } catch(InvalidJumlahAssetTokoException& e) {
        cout << "Jumlah barang yang ingin dijual tidak sesuai." << endl;
    }
}

void Toko::setJumlah(Asset* asset, int n) {
    if (n < 0) {
        throw InvalidJumlahAssetTokoException();
    }
    if (asset->getAssetType() == "BANGUNAN" || asset->getAssetType() == "PRODUK") {
        if (listJumlahAsset[asset->getKodeHuruf()] == 0 && n > 0) {
            addTersedia(asset);
        }
        if (listJumlahAsset[asset->getKodeHuruf()] > 0 && n == 0) {
            removeTersedia(asset);
        }
        listJumlahAsset[asset->getKodeHuruf()] = n;
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
        if (asset->getKodeHuruf() == a->getKodeHuruf()) {
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

void Toko::displayToko() {
    cout << "Selamat datang di toko!!" << endl;
    cout << "Berikut merupakan hal yang dapat Anda Beli" << endl;
    int n = this->listAssetTersedia.size();
    for (int i=0; i<n; i++) {
        cout << i+1 << ". " << this->listAssetTersedia[i]->getNamaAsset() << " - " << this->listAssetTersedia[i]->getPrice();
        if (i < this->jumlahBangunan + this->jumlahProduk) {
            cout << " (" << this->listJumlahAsset[this->listAssetTersedia[i]->getKodeHuruf()] << ")" << endl;
        } else {
            cout << endl;
        }
    }
}