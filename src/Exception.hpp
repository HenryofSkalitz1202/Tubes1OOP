#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <exception>
using namespace std;

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

#endif