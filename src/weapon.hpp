#pragma once

#include <string>

enum WeaponType : char {
    Improvised = 0,
    SimpleMelee,
    SimpleRanged,
    MartialMelee,
    MartialRanged,
    Firearm
};

struct SingleWeaponProficiency
{
    const std::string name;
    SingleWeaponProficiency(string name) : name(name) {};
    bool operator==(const SingleWeaponProficiency& other) {
        return name == other.name;
    }
};
