#pragma once

#include <string>
#include "selecter.hpp"
#include <iostream>
#include "time.hpp"

using namespace std;

class Character;

class Feat : public SelecterItem{
    public:
    virtual void update(Character& character, Selecter& selecter, UpdateType uType) = 0;
    virtual string getName() const = 0;
    virtual string getDescription() const = 0;
    string toString() const {
        return getName() + '\n' + getDescription();
    };
};