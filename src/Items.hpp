#ifndef ITEMS_HPP
#define ITEMS_HPP

// Base class untuk semua barang yang bisa dimasukkan ke inventory
// Diperlukan untuk grid
// Karena saya baru sadar template grid gabisa dipake kalau tumbuhan, hewan, produk, sama bangunan gapunya common parent class
// ehe 

#include <string>
using namespace std;

class Items {
    protected:
        string kodeHuruf;
        string type;
    public:
        Items();
        virtual ~Items() {};
        string getKodeHuruf();
        string getType();
};

#endif