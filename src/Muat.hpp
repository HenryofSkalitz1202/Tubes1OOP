#ifndef MUAT_HPP
#define MUAT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "Controller.hpp"

using namespace std;

class Muat {
    private:
    string filepath;
    Controller& controller;

    public:
    Muat(string filepath, Controller& controller);

    void read();
    Asset* getAsset(string name);
};

#endif