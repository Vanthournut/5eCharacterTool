#pragma once

#include <string>
#include <vector>
#include <memory>
#include "stat.hpp"
#include "proficiencies.hpp"
#include "spellcasting.hpp"
#include "race.hpp"
#include "armor.hpp"
#include "characterClass.hpp"

class Feat;
class AbilityScoreFeat;
class Selecter;

using namespace std;

static char defaultAbilityScores[6] = {10, 10, 10, 10, 10, 10};

class Character {

    private:

    string name;

    Race* race;

    // Proficiencies
    char proficiencyBonus;
    bool savingThrowProficiencies[6];
    vector<Proficiency> skillProficiencies;
    vector<ToolProficiency> toolProficiencies;
    vector<WeaponProficiency> weaponProficiencies;
    vector<Language> languages;
    bool armorProficiencies[4];

    // Feats & Actions
    vector<shared_ptr<Feat>> feats;
    ushort maxHP;
    ushort currentHP;
    char startingAbilityScores[6];
    char abilityScores[6];
    char speed;

    // Equipment
    shared_ptr<Armor> armor;
    vector<shared_ptr<ArmorClassModifier>> acModifiers;

    Spellcasting spellcasting;

    vector<Proficiency> getNewSkillVector();

    public:
    string getName();
    char getArmorClass();
    ushort getMaxHP();
    ushort getCurrentHP();
    char getAbilityScore(Stat stat);
    char getAbilityModifier(Stat stat);
    shared_ptr<Armor> getArmor();
    void addFeat(shared_ptr<Feat> feat);
    void addAbilityScore(Stat stat, char quantity);
    void addRace(Race* race);
    
    void addAcModifier(shared_ptr<ArmorClassModifier> modifier);

    bool addSkillProficiency(Skill skill);
    bool addLanguage(string name, bool speak, bool read, bool write);

    bool isProficient(Skill skill);

    void update();

    string toString();

    Character(string name, char stats[6] = defaultAbilityScores);

};