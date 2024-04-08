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
#endif