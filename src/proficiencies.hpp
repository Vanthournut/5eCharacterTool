#pragma once
#include <string>
#include "dice.hpp"
#include <vector>
#include "stat.hpp"
#include "selecter.hpp"

using namespace std;

class Character;

enum Skill : char {
    Acrobatics,
    AnimalHandling,
    Arcana,
    Athletics,
    Deception,
    History,
    Insight,
    Intimidation,
    Investigation,
    Medicine,
    Nature,
    Perception,
    Performance,
    Persuasion,
    Religion,
    SleightOfHand,
    Stealth,
    Survival
};

static vector<string> SKILL_NAME = {"Acrobatics", "Animal Handling", "Arcana", "Athletics", "Deception", "History", "Insight", "Intimidation", \
    "Investigation", "Medicine", "Nature", "Perception", "Performance", "Persuasion", "Religion", "Sleight of Hand", "Stealth", "Survival"};

enum ToolType : char {
    ArtisansTool,
    GamingSet,
    MusicalInstrument,
    Vehicle,
    OtherToolType
};

static const string ArtisansTools[19] {
    "Alchemist's Supplies",
    "Brewer's Supplies",
    "Calligrapher's Supplies",
    "Carpenter's Tools",
    "Cartographer's Tools",
    "Cobbler's Tools",
    "Cook's Utensils",
    "Glassblower's Tools",
    "Jeweler's Tools",
    "Leatherworker's Tools",
    "Mason's Tools",
    "Painter's Supplies",
    "Potter's Tools",
    "Smith's Tools",
    "Tinker's Tools",
    "Weaver's Tools",
    "Woodcarver's Tools"
};

static const string GamingSets[2] {
    "Dice Set",
    "Playing Card Set"
};

static const string MusicalInstruments[10] {
    "Bagpipes",
    "Drum",
    "Dulcimer",
    "Flute",
    "Lute",
    "Lyre",
    "Horn",
    "PanFlute",
    "Shawm",
    "Viol"
};

static const string OtherTools[7] {
    "Disguise Kit",
    "Forgery Kit",
    "Navigator's Tools",
    "Poisoner's Kit",
    "Thieve's Tools",
    "Vehicles (Land)",
    "Vehicles (Water)"
};



static Stat getDefaultStat(Skill skill) {
    static const Stat defaultSkillStat[18] = {
        Stat::Dexterity,    // Acrobatics
        Stat::Wisdom,       // Animal Handling
        Stat::Intelligence, // Arcana
        Stat::Strength,     // Athletics
        Stat::Charisma,     // Deception
        Stat::Intelligence, // History
        Stat::Wisdom,       // Insight
        Stat::Charisma,     // Intimidation
        Stat::Intelligence, // Investigation
        Stat::Wisdom,       // Medicine
        Stat::Intelligence, // Natures
        Stat::Wisdom,       // Perception
        Stat::Charisma,     // Persuasion
        Stat::Charisma,     // Performance
        Stat::Intelligence, // Religion
        Stat::Dexterity,    // Sleight Of Hand
        Stat::Dexterity,    // Stealth
        Stat::Wisdom        // Survival
    };

    return defaultSkillStat[skill];
}

class SkillSelecterItem : public SelecterItem {
    public:
    const Skill s;
    SkillSelecterItem(Skill s) : s(s) {}
    string getName() const override {return SKILL_NAME[s];};
    string getDescription() const override {return "";}
};

class Proficiency {
    string name;

    public:
    bool isProficient;
    DicePool bonus;

    Proficiency(string name) : name(name), isProficient(false) {};

    string toString() const;
    string toStringWithStat(const Character& c, Stat stat) const;
};

class ToolProficiency : public Proficiency {
};

class Language {
    const string name;
    bool speak;
    bool read;
    bool write;

    public:
    Language(string name, bool speak, bool read, bool write) 
    : name(name), speak(speak), read(read), write(write) {
    };
};