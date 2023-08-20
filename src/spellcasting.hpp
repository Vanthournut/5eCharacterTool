#include <vector>
#include <string>
#include "stat.hpp"

using namespace std;

class Spellcasting {
    float level;
    char spellSlots[9];
    vector<SpellcastingSource> sources;
};

class SpellcastingSource {
    char attackBonus;
    char saveDC;
    Stat spellcastingAbilitity;
    vector<Spell> spells;
};

class Spell{
    virtual string getName();
    virtual string getDescription();
};