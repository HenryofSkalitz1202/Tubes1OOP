#include "Items.hpp"

Items::Items() {
    this->kodeHuruf = "-";
    this->type = "-";
}

string Items::getKodeHuruf() {
    return this->kodeHuruf;
}

string Items::getType() {
    return this->type;
}