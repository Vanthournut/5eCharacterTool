#pragma once

#include <string>
#include "selecter.hpp"
#include <iostream>

using namespace std;

class Character;

class Feat : public SelecterItem{
    public:
    virtual void update(Character& character) = 0;
    virtual string getName() const = 0;
    virtual string getDescription() const = 0;
    string toString() const {
        return getName() + '\n' + getDescription();
    };
};