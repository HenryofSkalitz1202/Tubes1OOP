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

struct NotHerbivoreException : public exception{
    const char* what() const throw(){
        return " bukan herbivore.\n";
    }
};

struct NotCarnivoreException : public exception{
    const char* what() const throw(){
        return " bukan carnivore.\n";
    }
};

struct NotOmnivoreException : public exception{
    const char* what() const throw(){
        return " bukan omnivore.\n";
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

struct HerbivoreWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return "Herbivore can only eat ProductFruit type.\n";
    }
};

struct CarnivoreWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return "Carnivore can only eat ProductHewan type.\n";
    }
};

struct OmnivoreWrongFoodTypeException : public exception{
    const char* what() const throw(){
        return "Omnivore can only eat ProductFruit or ProductHewan type.\n";
    }
};

struct insertIntoUnemptyCellException : public exception{
    const char* what() const throw(){
        return "Value can only be inserted on empty cells.\n";
    }
};

struct inventoryEmptyException : public exception{
    const char* what() const throw(){
        return "Inventory is empty!\n";
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

#endif