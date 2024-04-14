#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <exception>
using namespace std;

class FilePathProdukNotFoundException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m' is not found.\n\033[0m";
    }
};

class FilePathHewanNotFoundException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m' is not found.\n\033[0m";
    }
};

class FilePathTumbuhanNotFoundException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m' is not found.\n\033[0m";
    }
};

class FilePathBangunanNotFoundException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m' is not found.\n\033[0m";
    }
};

class FilePathMiscNotFoundException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m' is not found.\n\033[0m";
    }
};

class missingDataException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m\033[1;31mIt seems that there are missing data. Please recheck your config file\033[0m";
    }
};

class UnexpectedDataException : public std::exception {
public:
    const char* what() const noexcept override {
        return "\033[1;31mIt seems that there are unexpected additional data. Please recheck your config file!\n\033[0m";
    }
};

class duplicateKeyException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mDuplicate key value is detected!\n\033[0m";
    }
};

class invalidKodeHurufException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mKode huruf must consist of 3 capital alphabet letters!\n\033[0m";
    }
};

class invalidPriceException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mPrice of any Asset must have a positive value.\n\033[0m";
    }
}; 

class invalidWeightToHarvestException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mWeight to harvest of any Hewan must have a positive value.\n\033[0m";
    }
};

class invalidDurationToHarvestException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mDuration to harvest of any Tumbuhan must have a positive value.\n\033[0m";
    }
}; 

class invalidMaterialQuantityException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mQuantity of any material Bangunan must have a positive value.\n\033[0m";
    }
}; 

class BangunanFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of Bangunan type must have type 'BANGUNAN\n\033[0m";
    }
};

class ProdukFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of Produk type must have type 'PRODUK\n\033[0m";
    }
};

class HewanFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of Hewan type must have type 'HEWAN\n\033[0m";
    }
};

class TumbuhanFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of Tumbuhan type must have type 'TUMBUHAN\n\033[0m";
    }
};

class ProductMaterialFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of ProductMaterial type must have type 'PRODUCT_MATERIAL_PLANT\n\033[0m";
    }
};

class ProductFruitFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of ProductFruit type must have type 'PRODUCT_FRUIT_PLANT\n\033[0m";
    }
};

class ProductHewanFalseTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mObject of ProductHewan type must have type 'PRODUCT_ANIMAL\n\033[0m";
    }
};

class UnknownProductTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m is an unknown product type.\n\033[0m";
    }
};

class UnknownAnimalTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m is an unknown animal type.\n\033[0m";
    }
};

class UnknownPlantTypeException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m is an unknown plant type.\n\033[0m";
    }
};

class MaterialBangunanNotProductMaterialException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m is not of ProductMaterial type.\n\033[0m";
    }
};

class productMaterialNotFromMaterialPlantException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mProductMaterial must originate from a MaterialPlant.\n\033[0m";
    }
};

class productFruitNotFromFruitPlantException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mProductFruit must originate from a FruitPlant.\n\033[0m";
    }
};

class productHewanNotFromHewanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mProductHewan must originate from a Hewan.\n\033[0m";
    }
};

class productMaterialFalseAddedWeightException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mProductMaterial must have an added weight of 0 as it is inedible.\n\033[0m";
    }
};

class productFruitFalseAddedWeightException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mProductFruit must have a positive value for added weight as it is edible.\n\033[0m";
    }
};

class productHewanFalseAddedWeightException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mProductHewan must have a positive value for added weight as it is edible.\n\033[0m";
    }
};

class noFoodException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mYou don't have any food.\n\033[0m";
    }
};

class noMatchingFoodException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mYou don't have any matching food for your animals.\n\033[0m";
    }
};

class inventoryEmptyException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mInventory is empty!\n\033[0m";
    }
};

class inventoryNotEnoughException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mAvailable inventory capacity is not enough!\n\033[0m";
    }
};

class inventoryFullException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mInventory is full!\n\033[0m";
    }
};

class ladangEmptyException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mLadang is empty!\n\033[0m";
    }
};

class ladangFullException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mLadang is full!\n\033[0m";
    }
};

class peternakanEmptyException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mPeternakan is empty!\n\033[0m";
    }
};

class peternakanFullException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mPeternakan is full!\n\033[0m";
    }
};

class noneSiapPanenLadangException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m\\('u')/ Sing sabar, sing tenang \\('u')/\nNo tanaman is ready for panen yet!\n\033[0m";
    }
};

class noneSiapPanenPeternakanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m\\('u')/ Sing sabar, sing tenang \\('u')/\nNo hewan is ready for panen yet!\n\033[0m";
    }
};

class tanamNotTumbuhanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m You can only plant object of Tumbuhan type.\n\033[0m";
    }
};

class noHewanAvailableException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mYou don't have any Hewan on your inventory!\n\033[0m";
    }
};

class noTumbuhanAvailableException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mYou don't have any Hewan on your inventory!\n\033[0m";
    }
};

class ternakNotHewanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31m You can only raise object of Hewan type.\n\033[0m";
    }
};

class invalidNomorTanamanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mNomor tanaman is invalid!\n\033[0m";
    }
};

class invalidNomorHewanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mNomor hewan is invalid!\n\033[0m";
    }
};

class invalidJumlahPetakException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mJumlah petak is invalid!\n\033[0m";
    }
};

class invalidKeyException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mKey is invalid!\n\033[0m";
    }
};

class invalidPetakException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mPilihan petak is invalid!\n\033[0m";
    }
};

class invalidNamaBangunanException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mPilihan petak is invalid!\n\033[0m";
    }
};

class uangInsufficientException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mUang tidak cukup untuk apapun!\n\033[0m";
    }
};

class invalidStoiException : public exception{
public:
    const char* what() const noexcept override{
        return "\033[1;31mExpected integer but found non-numeric characters!\n\033[0m";
    }
};
#endif