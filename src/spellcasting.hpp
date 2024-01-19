#pragma once

#include <vector>
#include <string>
#include "stat.hpp"
#include "selecter.hpp"
#include "time.hpp"

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

struct SpellComponents
{
    bool verbal;
    bool somatic;
    string material;
    int materialCost;
    bool materialConsumed;
};

class Spell : public SelecterItem {
    virtual SpellSchool getSchool() const = 0;
    virtual SpellLevel getSpellLevel() const = 0;
    virtual TimeDuration getCastingTime() const = 0;
    virtual bool isConcentration() const = 0;
    virtual bool isRitual() const = 0;
    virtual SpellComponents getComponents() const = 0;
    virtual vector<string> getTags() const = 0;
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
    string getName() const override {return "Spellcasting Spell Slots";};
    string getDescription() const override {return "";};
    bool isSpellcaster() {return innateSpellcaster;};
};

// TODO
// Master vector of spells
// Clone spell to create a new one
// - Will not apply to altered version of spells
// Wrap in container to prevent contamination

class AcidSplash : public Spell {
    public:
    string getName() const override {return "Acid Splash";};
    string getDescription() const  override {return "You hurl a bubble of acid. Choose one creature you can see within range, or choose two creatures you can see within range that are within 5 feet of each other. A target must succeed on a Dexterity saving throw or take 1d6 acid damage.\nThis spell's damage increases by 1d6 when you reach 5th level (2d6), 11th level (3d6), and 17th level (4d6).";};
    SpellSchool getSchool() const override {return SpellSchool::Conjuration;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
};

static AcidSplash ACID_SPLASH = AcidSplash();

class ChillTouch : public Spell {
    public:
    string getName() const override {return "Chill Touch";};
    string getDescription() const  override {return "You create a ghostly, skeletal hand in the space of a creature within range. Make a ranged spell attack against the creature to assail it with the chill of the grave. On a hit, the target takes 1d8 necrotic damage, and it can't regain hit points until the start of your next turn. Until then, the hand clings to the target.\n\n\
If you hit an undead target, it also has disadvantage on attack rolls against you until the end of your next turn.\n\n\
This spell's damage increases by 1d8 when you reach 5th level (2d8), 11th level (3d8), and 17th level (4d8).";};
    SpellSchool getSchool() const override {return SpellSchool::Necromancy;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
};

static ChillTouch CHILL_TOUCH = ChillTouch();


extern vector<Spell*> WIZARD_SPELL_LIST;
extern vector<SelecterItem*> WIZARD_SPELL_SELECTOR;