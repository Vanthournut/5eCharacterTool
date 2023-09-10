#include <vector>
#include <string>
#include "stat.hpp"
#include "selecter.hpp"

using namespace std;

class Spellcasting : public SpellSlotSource {
    float level;
    char spellSlots[9];
    vector<SpellcastingSource> spellcastingSources;
    vector<SpellSlotSource> SpellSlotSources;
    void update() override {};
};

class SpellcastingSource {
    char attackBonus;
    char saveDC;
    Stat spellcastingAbilitity;
    vector<Spell> spells;
};

class SpellSlotSource : public SelecterItem {
    char spellSlots[9];
    virtual void update();
};

class Spell{
    virtual string getName();
    virtual string getDescription();
    virtual char getSchool();
    virtual char getSpellLevel();
    virtual char getCastingTime();
    virtual bool isConcentration();
    virtual bool isRitual();
    virtual vector<bool> getComponents();
};