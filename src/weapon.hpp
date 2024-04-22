#pragma once

#include <string>

enum WeaponType : char {
    Unarmed = 0,
    Improvised,
    SimpleMelee,
    SimpleRanged,
    MartialMelee,
    MartialRanged,
    Firearm
};

struct SingleWeaponProficiency
{
    const std::string name;
    bool operator==(const SingleWeaponProficiency& other) {
        return name == other.name;
    }
};
