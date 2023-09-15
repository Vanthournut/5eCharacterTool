#include <vector>
#include <string>
#include "stat.hpp"
#include "selecter.hpp"

using namespace std;

enum SpellSchool : char {
    Abjuration,
    Conjuration,
    Divination,
    Enchantment,
    Evocation,
    Illusion,
    Necromancy,
    Transmutaion
};

enum SpellLevel : char {
    Cantrip,
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Seventh,
    Eighth,
    Nineth
};

class Spell : public SelecterItem {
    virtual SpellSchool getSchool();
    virtual SpellLevel getSpellLevel();
    virtual char getCastingTime();
    virtual bool isConcentration();
    virtual bool isRitual();
    virtual vector<bool> getComponents();
    virtual vector<string> getTags();
};

class SpellcastingSource {
    char attackBonus;
    char saveDC;
    Stat spellcastingAbilitity;
    vector<Spell> spells;
};

class SpellSlotSource : public SelecterItem {
    char spellSlots[9];
    virtual void update() = 0;
};

class Spellcasting : public SpellSlotSource {
    float level;
    char spellSlots[9];
    vector<SpellcastingSource> spellcastingSources;
    vector<SpellSlotSource> SpellSlotSources;
    bool innateSpellcaster;

    public:
    void update() override {};
    string getName() override {return "Spellcasting Spell Slots";};
    string getDescription() override {return "";};
    bool isSpellcaster() {return innateSpellcaster;};
};

// TODO
// Master vector of spells
// Clone spell to create a new one
// - Will not apply to altered version of spells
// Wrap in container to prevent contamination