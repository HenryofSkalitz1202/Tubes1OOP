#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <exception>
using namespace std;

class InvalidMakananException : public exception{
    public:
        InvalidMakananException(): exception() {}

        const char* what() const throw(){
            return "Makanan tidak sesuai. Mohon masukkan makanan yang sesuai.\n";
        }
};

#endif