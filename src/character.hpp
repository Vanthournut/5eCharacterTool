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
#include "weapon.hpp"

class Feat;
class AbilityScoreFeat;
class Selecter;

using namespace std;

static char defaultAbilityScores[6] = {10, 10, 10, 10, 10, 10};

class Character {

    private:

    string name;

    Race* race;
    vector<CharacterClass*> classes;

    // Proficiencies
    char proficiencyBonus;
    bool savingThrowProficiencies[6];
    vector<Proficiency> skillProficiencies;
    vector<ToolProficiency> toolProficiencies;
    bool armorProficiencies[4];
    bool weaponProficiencies[6];
    vector<SingleWeaponProficiency> singleWeaponProficiencies;
    
    vector<Language> languages;

    // Feats & Actions
    vector<shared_ptr<Feat>> feats;
    char startingAbilityScores[6];
    char abilityScores[6];
    char speed;

    ushort maxHP;
    ushort currentHP;
    char level;

    // Equipment
    shared_ptr<Armor> armor;
    vector<shared_ptr<ArmorClassCalculator>> acCalculators;
    vector<shared_ptr<ArmorClassModifier>> acModifiers;

    Spellcasting spellcasting;

    vector<Proficiency> getNewSkillVector();

    public:
    string getName();
    ushort getMaxHP();
    ushort getCurrentHP();
    char getAbilityScore(Stat stat);
    char getAbilityModifier(Stat stat);
    shared_ptr<Armor> getArmor();
    void addFeat(shared_ptr<Feat> feat);
    void addAbilityScore(Stat stat, char quantity);
    void addRace(Race* race);
    void addClass(CharacterClass* charClass);
    
    // Armor Class Functions
    void addAcModifier(shared_ptr<ArmorClassModifier> modifier);
    void addAcCalculator(shared_ptr<ArmorClassCalculator> calculator);
    char getArmorClass();

    bool addLanguage(string name, bool speak, bool read, bool write);

    // Adding Proficiencies
    bool addSkillProficiency(Skill skill);
    void addSavingThrowProficiency(Stat stat);
    void addArmorProficiency(ArmorType armorType);
    void addWeaponProficiency(WeaponType weaponType);
    void addWeaponProficiency(SingleWeaponProficiency weaponType);

    // Proficiency Checks
    bool isProficient(Skill skill);
    bool isProficient(ArmorType armorType);
    bool isProficient(WeaponType weaponType);
    bool isProficient(SingleWeaponProficiency weaponType);

    void update();

    string toString();

    Character(string name, char stats[6] = defaultAbilityScores);

};