#include "Toko.hpp"
#include "Exception.hpp"

Toko::Toko() {
    for (auto const& x: Bangunan::resepBangunan) {
        this->listJumlahAsset[x.first] = 0;
    }
    for (auto const& x: ProductMaterial::configProdukMaterial) {
        this->listJumlahAsset[x.first] = 0;
    }
    for (auto const& x: ProductFruit::configProdukFruit) {
        this->listJumlahAsset[x.first] = 0;
    }
    for (auto const& x: ProductHewan::configProdukHewan) {
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
        int assetPrice = listAssetTersedia[pilihan-1]->getPrice();
        int cost = jumlah*assetPrice;
        if (cost > uang) {
            throw NotEnoughMoneyException();
        }
        uang -= cost;
        if (this->listAssetTersedia[pilihan-1]->getAssetType() == "BANGUNAN" || this->listAssetTersedia[pilihan-1]->getAssetType() == "PRODUK") {
            setJumlah(assetName, getJumlah(assetName) - jumlah);
        }
        return listAssetTersedia[pilihan-1];
    } catch(InvalidJumlahAssetTokoException& e) {
        std::cout << "Jumlah barang yang ingin dibeli tidak sesuai." << endl;
    } catch(InvalidPilihanBeliException& e) {
        std::cout << e.what() << endl;
    } catch(NotEnoughMoneyException& e) {
        std::cout << e.what() << endl;
    }
    return nullptr;
}

int Toko::jual(vector<Asset*> listItem) {
    int totalHarga = 0;
    for (auto const& item: listItem) {
        if (item->getAssetType() == "BANGUNAN" || item->getAssetType() == "PRODUK") {
            setJumlah(item->getNamaAsset(), getJumlah(item->getNamaAsset()) + 1);
        }
        totalHarga += item->getPrice();
    }
    return totalHarga;
}

void Toko::setJumlah(string name, int n) {
    if (this->listJumlahAsset.count(name)) {
        if (n < 0) {
            throw InvalidJumlahAssetTokoException();
        }
        if (this->listJumlahAsset[name] == 0 && n > 0) {
            if (Bangunan::resepBangunan.count(name) != 0) {
                addTersedia(Bangunan::resepBangunan[name]);
            } else if (ProductMaterial::configProdukMaterial.count(name) != 0) {
                addTersedia(ProductMaterial::configProdukMaterial[name]);
            } else if (ProductFruit::configProdukFruit.count(name) != 0) {
                addTersedia(ProductFruit::configProdukFruit[name]);
            } else if (ProductHewan::configProdukHewan.count(name) != 0) {
                addTersedia(ProductHewan::configProdukHewan[name]);
            }
        }
        if (this->listJumlahAsset[name] > 0 && n == 0) {
            if (Bangunan::resepBangunan.count(name) != 0) {
                removeTersedia(Bangunan::resepBangunan[name]);
            } else if (ProductMaterial::configProdukMaterial.count(name) != 0) {
                removeTersedia(ProductMaterial::configProdukMaterial[name]);
            } else if (ProductFruit::configProdukFruit.count(name) != 0) {
                removeTersedia(ProductFruit::configProdukFruit[name]);
            } else if (ProductHewan::configProdukHewan.count(name) != 0) {
                removeTersedia(ProductHewan::configProdukHewan[name]);
            }
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

map<string, int> Toko::getListJumlahAsset() {
    map<string, int> jumlahAsset;
    for (auto const& x: this->listJumlahAsset) {
        if (x.second > 0) {
            jumlahAsset[x.first] = x.second;
        }
    }
    return jumlahAsset;
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