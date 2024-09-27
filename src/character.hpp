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
#include "sourceBook.hpp"

class Feat;
class AbilityScoreFeat;
class Selecter;

using namespace std;

static char defaultAbilityScores[6] = {10, 10, 10, 10, 10, 10};

class Character {

    private:
    SourceBookManager sourceBooks;

    bool loaded = false; // Used to determine if loaded from file / istream. Required to correctly clean memory of constructed pointers

    string name;

    Race* race;
    vector<CharacterClass*> classes;

    // Proficiencies
    char proficiencyBonus;
    bool savingThrowProficiencies[6] = {};
    bool armorProficiencies[4] = {};
    bool weaponProficiencies[6] = {};
    vector<Proficiency> skillProficiencies;
    vector<ToolProficiency> toolProficiencies;
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
    string getName() const;
    ushort getMaxHP() const;
    ushort getCurrentHP() const;
    char getAbilityScore(Stat stat) const;
    char getAbilityModifier(Stat stat) const;
    shared_ptr<Armor> getArmor() const;
    void addFeat(shared_ptr<Feat> feat);
    void addAbilityScore(Stat stat, char quantity);
    void addRace(Race* race);
    void addClass(CharacterClass* charClass);
    
    // Armor Class Functions
    void addAcModifier(shared_ptr<ArmorClassModifier> modifier);
    void addAcCalculator(shared_ptr<ArmorClassCalculator> calculator);
    char getArmorClass() const;

    bool addLanguage(string name, bool speak, bool read, bool write);

    // Adding Proficiencies
    bool addSkillProficiency(Skill skill);
    void addSavingThrowProficiency(Stat stat);
    void addArmorProficiency(ArmorType armorType);
    void addWeaponProficiency(WeaponType weaponType);
    void addWeaponProficiency(SingleWeaponProficiency weaponType);

    // Proficiency Checks
    bool isProficient(Skill skill) const;
    bool isProficient(ArmorType armorType) const;
    bool isProficient(WeaponType weaponType) const;
    bool isProficient(SingleWeaponProficiency weaponType) const;


    void update(Selecter& selecter, UpdateType uType);
    template <class Predicate>
    void getSpellList(string listName, vector<Spell*>& returnVector, Predicate predicate = nullptr) const {
        sourceBooks.getSpellList(listName, returnVector, predicate);
    };

    string toString() const;

    // Saving and Loading
    void save(ostream& outputStream);
    static Character* load(istream& inputStream);

    bool operator==(const Character& c2) {
        return toString() == c2.toString();
    }

    Character(string name, char stats[6] = defaultAbilityScores);
    ~Character();

};