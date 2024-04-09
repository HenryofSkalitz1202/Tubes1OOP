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
        return "Object of Bangunan type doesn't have type 'BANGUNAN";
    }
};

struct ProdukFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of Produk type doesn't have type 'PRODUK";
    }
};

struct ProductMaterialFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductMaterial type doesn't have type 'PRODUCT_MATERIAL_PLANT";
    }
};

struct ProductFruitFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductFruit type doesn't have type 'PRODUCT_FRUIT_PLANT";
    }
};

struct ProductHewanFalseTypeException : public exception{
    const char* what() const throw(){
        return "Object of ProductHewan type doesn't have type 'PRODUCT_ANIMAL";
    }
};

struct NotHerbivoreException : public exception{
    const char* what() const throw(){
        return " bukan herbivore.";
    }
};

struct NotCarnivoreException : public exception{
    const char* what() const throw(){
        return " bukan carnivore.";
    }
};

struct NotOmnivoreException : public exception{
    const char* what() const throw(){
        return " bukan omnivore.";
    }
};

struct UnknownProductTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown product type.";
    }
};

struct UnknownAnimalTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown animal type.";
    }
};

struct UnknownPlantTypeException : public exception{
    const char* what() const throw(){
        return " is an unknown plant type.";
    }
};

struct MaterialBangunanNotProductMaterialException : public exception{
    const char* what() const throw(){
        return " is not of ProductMaterial type.";
    }
};

#endif