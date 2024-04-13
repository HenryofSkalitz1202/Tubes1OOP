#ifndef MUAT_HPP
#define MUAT_HPP

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Controller;

class Muat {
    private:
    string filepath;
    Controller& controller;

    public:
    Muat(string filepath, Controller& controller);

    void read();
};

#endif