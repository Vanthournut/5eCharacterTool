#pragma once

#include <string>

using namespace std;

enum Stat : char {
    Strength = 0,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma
};

static const vector<string> STAT_NAMES = {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
static const vector<string> STAT_SHORT = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};