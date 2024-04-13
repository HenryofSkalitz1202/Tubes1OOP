#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <exception>
using namespace std;

struct FilePathProdukNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

struct FilePathHewanNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

struct FilePathTumbuhanNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

struct FilePathBangunanNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

struct FilePathMiscNotFoundException : public exception{
    const char* what() const throw(){
        return "' is not found.";
    }
};

struct BangunanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Bangunan type doesn't have type 'BANGUNAN\n";
    }
};

struct ProdukFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Produk type doesn't have type 'PRODUK\n";
    }
};

struct HewanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Hewan type doesn't have type 'Hewan\n";
    }
};

struct TumbuhanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Tumbuhan type doesn't have type 'Tumbuhan\n";
    }
};

struct ProductMaterialFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductMaterial type doesn't have type 'PRODUCT_MATERIAL_PLANT\n";
    }
};

struct ProductFruitFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductFruit type doesn't have type 'PRODUCT_FRUIT_PLANT\n";
    }
};

struct ProductHewanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductHewan type doesn't have type 'PRODUCT_ANIMAL\n";
    }
};

struct UnknownProductTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown product type.\n";
    }
};

struct UnknownAnimalTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown animal type.\n";
    }
};

struct UnknownPlantTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown plant type.\n";
    }
};

struct MaterialBangunanNotProductMaterialException : public exception{
    const char* what() const throw(){
        return " is not of ProductMaterial type.\n";
    }
};

struct noFoodException : public exception{
    const char* what() const throw(){
        return "You don't have any food.\n";
    }
};

struct noMatchingFoodException : public exception{
    const char* what() const throw(){
        return "You don't have any matching food for your animals.\n";
    }
};

struct inventoryEmptyException : public exception{
    const char* what() const throw(){
        return "Inventory is empty!\n";
    }
};

struct inventoryNotEnoughException : public exception{
    const char* what() const throw(){
        return "Available inventory capacity is not enough!\n";
    }
};

struct inventoryFullException : public exception{
    const char* what() const throw(){
        return "Inventory is full!\n";
    }
};

struct ladangEmptyException : public exception{
    const char* what() const throw(){
        return "Ladang is empty!\n";
    }
};

struct ladangFullException : public exception{
    const char* what() const throw(){
        return "Ladang is full!\n";
    }
};

struct peternakanEmptyException : public exception{
    const char* what() const throw(){
        return "Peternakan is empty!\n";
    }
};

struct peternakanFullException : public exception{
    const char* what() const throw(){
        return "Peternakan is full!\n";
    }
};

struct noneSiapPanenLadangException : public exception{
    const char* what() const throw(){
        return "\\('u')/ Sing sabar, sing tenang \\('u')/\nNo tanaman is ready for panen yet!\n";
    }
};

struct noneSiapPanenPeternakanException : public exception{
    const char* what() const throw(){
        return "\\('u')/ Sing sabar, sing tenang \\('u')/\nNo hewan is ready for panen yet!\n";
    }
};

struct tanamNotTumbuhanException : public exception{
    const char* what() const throw(){
        return " You can only plant object of Tumbuhan type.\n";
    }
};

struct noHewanAvailableException : public exception{
    const char* what() const throw(){
        return "You don't have any Hewan on your inventory!\n";
    }
};

struct noTumbuhanAvailableException : public exception{
    const char* what() const throw(){
        return "You don't have any Hewan on your inventory!\n";
    }
};

struct ternakNotHewanException : public exception{
    const char* what() const throw(){
        return " You can only raise object of Hewan type.\n";
    }
};

struct invalidNomorTanamanException : public exception{
    const char* what() const throw(){
        return "Nomor tanaman is invalid!\n";
    }
};

struct invalidNomorHewanException : public exception{
    const char* what() const throw(){
        return "Nomor hewan is invalid!\n";
    }
};

struct invalidJumlahPetakException : public exception{
    const char* what() const throw(){
        return "Jumlah petak is invalid!\n";
    }
};

struct invalidKeyException : public exception{
    const char* what() const throw(){
        return "Key is invalid!\n";
    }
};

struct invalidPetakException : public exception{
    const char* what() const throw(){
        return "Pilihan petak is invalid!\n";
    }
};

struct invalidNamaBangunanException : public exception{
    const char* what() const throw(){
        return "Pilihan petak is invalid!\n";
    }
};

struct uangInsufficientException : public exception{
    const char* what() const throw(){
        return "Uang tidak cukup!\n";
    }
};

#endif