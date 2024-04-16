#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <exception>
using namespace std;

class FilePathStateNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

class FilePathProdukNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

class FilePathHewanNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

class FilePathTumbuhanNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

class FilePathBangunanNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

class SavePathNotFoundException : public exception{
    const char* what() const throw(){
        return "File path invalid.";
    }
};

class BangunanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Bangunan type doesn't have type 'BANGUNAN\n";
    }
};

class ProdukFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Produk type doesn't have type 'PRODUK\n";
    }
};

class HewanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Hewan type doesn't have type 'Hewan\n";
    }
};

class TumbuhanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Tumbuhan type doesn't have type 'Tumbuhan\n";
    }
};

class ProductMaterialFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductMaterial type doesn't have type 'PRODUCT_MATERIAL_PLANT\n";
    }
};

class ProductFruitFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductFruit type doesn't have type 'PRODUCT_FRUIT_PLANT\n";
    }
};

class ProductHewanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductHewan type doesn't have type 'PRODUCT_ANIMAL\n";
    }
};

class NotHerbivoreException : public exception{
    const char* what() const throw(){
        return " bukan herbivore.\n";
    }
};

class NotCarnivoreException : public exception{
    const char* what() const throw(){
        return " bukan carnivore.\n";
    }
};

class NotOmnivoreException : public exception{
    const char* what() const throw(){
        return " bukan omnivore.\n";
    }
};

class UnknownProductTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown product type.\n";
    }
};

class UnknownAnimalTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown animal type.\n";
    }
};

class UnknownPlantTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown plant type.\n";
    }
};

class MaterialBangunanNotProductMaterialException : public exception{
    const char* what() const throw(){
        return " is not of ProductMaterial type.\n";
    }
};

class HewanWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return ". Hewan can only eat Produk type.\n";
    }
};

class HerbivoreWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return "Herbivore can only eat ProductFruit type.\n";
    }
};

class CarnivoreWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return "Carnivore can only eat ProductHewan type.\n";
    }
};

class OmnivoreWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return "Omnivore can only eat ProductFruit or ProductHewan type.\n";
    }
};

class insertIntoUnemptyCellException : public exception{
    const char* what() const throw(){
        return "Value can only be inserted on empty cells.\n";
    }
};

class isAlreadyNullException : public exception{
    const char* what() const throw(){
        return "Value of given cell is already null!\n";
    }
};

class outOfBoundsException : public exception{
    const char* what() const throw(){
        return " .Index is out of bounds!\n";
    }
};

class inventoryEmptyException : public exception{
    const char* what() const throw(){
        return "Inventory is empty!\n";
    }
};

class inventoryFullException : public exception{
    const char* what() const throw(){
        return "Inventory is full!\n";
    }
};

class ladangEmptyException : public exception{
    const char* what() const throw(){
        return "Ladang is empty!\n";
    }
};

class ladangFullException : public exception{
    const char* what() const throw(){
        return "Ladang is full!\n";
    }
};

class noneSiapPanenLadangException : public exception{
    const char* what() const throw(){
        return "\\('u')/ Sing sabar, sing tenang \\('u')/\nNo tanaman is ready for panen yet!\n";
    }
};

class noneSiapPanenPeternakanException : public exception{
    const char* what() const throw(){
        return "\\('u')/ Sing sabar, sing tenang \\('u')/\nNo hewan is ready for panen yet!\n";
    }
};

class peternakanEmptyException : public exception{
    const char* what() const throw(){
        return "Peternakan is empty!\n";
    }
};

class peternakanFullException : public exception{
    const char* what() const throw(){
        return "Peternakan is full!\n";
    }
};

class tanamNotTumbuhanException : public exception{
    const char* what() const throw(){
        return " You can only plant object of Tumbuhan type.\n";
    }
};

class ternakNotHewanException : public exception{
    const char* what() const throw(){
        return " You can only raise object of Hewan type.\n";
    }
};

class InvalidMakananException : public exception{
    public:
        InvalidMakananException(): exception() {}

        const char* what() const throw(){
            return "Makanan tidak sesuai. Mohon masukkan makanan yang sesuai.\n";
        }
};

class invalidNomorTanamanException : public exception{
    const char* what() const throw(){
        return "Nomor tanaman is invalid!\n";
    }
};

class invalidNomorHewanException : public exception{
    const char* what() const throw(){
        return "Nomor hewan is invalid!\n";
    }
};

class invalidJumlahPetakException : public exception{
    const char* what() const throw(){
        return "Jumlah petak is invalid!\n";
    }
};

class invalidKeyException : public exception{
    const char* what() const throw(){
        return "Key is invalid!\n";
    }
};

class invalidPetakException : public exception{
    const char* what() const throw(){
        return "Pilihan petak is invalid!\n";
    }
};

class InvalidJumlahAssetTokoException : public exception{
    public:
        InvalidJumlahAssetTokoException(): exception() {}

        const char* what() const throw(){
            return "Jumlah barang tidak sesuai.";
        }
};

class InvalidPilihanBeliException : public exception{
    public:
        InvalidPilihanBeliException(): exception() {}

        const char* what() const throw(){
            return "Pilihan barang yang ingin dibeli tidak sesuai.\n";
        }
};

class gameNotStartedException : public exception{
    const char* what() const throw(){
        return "Game sedang tidak berjalan!\n";
    }
};

class wrongPlayerTypeException : public exception{
    const char* what() const throw(){
        return "Kamu tidak bisa melakukan itu!\n";
    }
};

class notEnoughMoneyException : public exception{
    const char* what() const throw(){
        return "Uang tidak cukup!\n";
    }
};

class pemainFalseTypeException : public exception{
    const char* what() const throw(){
        return "Kamu hanya bisa menambahkan pemain dengan tipe \"peternak\" atau \"petani\"!\n";
    }
};

class usernameNotUniqueException : public exception{
    const char* what() const throw(){
        return "Username tersebut sudah digunakan pemain lain!\n";
    }
};

class NotEnoughMoneyException : public exception{
    public:
        NotEnoughMoneyException(): exception() {}

        const char* what() const throw(){
            return "Uang tidak cukup.\n";
        }
};

class NotEnoughInventoryException : public exception{
    public:
        NotEnoughInventoryException(): exception() {}

        const char* what() const throw(){
            return "Inventory tidak cukup.\n";
        }
};

class commandNotFoundException : public exception{
    const char* what() const throw(){
        return "Pilihan tidak ditemukan, coba periksa kembali!\n";
    }
};

#endif