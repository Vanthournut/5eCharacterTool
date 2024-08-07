#include <string>
#include <vector>
#include <algorithm>
#include "character.hpp"
#include "proficiencies.hpp"
#include "feats.hpp"
#include "sourceList.hpp"

Character::Character(string name, char stats[6]) {
    loaded = false;
    for(int i = 0; i < 6; ++i) {
        abilityScores[i] = stats[i];
        startingAbilityScores[i] = stats[i];
    }

    this->name = name;
    maxHP = 0;
    currentHP = maxHP;
    speed = 30;
    proficiencyBonus = 2;

    level = 0;
    race = nullptr;
    classes = vector<CharacterClass*>();

    skillProficiencies = getNewSkillVector();
    toolProficiencies = vector<ToolProficiency>();
    singleWeaponProficiencies = vector<SingleWeaponProficiency>();
    
    languages = vector<Language>();

    feats = vector<shared_ptr<Feat>>();

    armor = shared_ptr<Armor>(new Unarmored());
    acCalculators = vector<shared_ptr<ArmorClassCalculator>>();
    acModifiers = vector<shared_ptr<ArmorClassModifier>>();
}

Character::~Character() {
    if(loaded) {
        delete race;

        for(auto cClass : classes) {
            delete cClass;
        }
    }
}

string Character::getName() const {
    return name;
}

char Character::getArmorClass() const {
    char ac = armor->getArmorClass(*this);

    for(auto acCalculator : acCalculators) {
        if(acCalculator->calculateArmorClass(*this) > ac) {
            ac = acCalculator->calculateArmorClass(*this);
        }
    }

    for(auto modifier : acModifiers) {
        ac = modifier->modifyArmorClass(*this, ac);
    }
    return ac;
}

ushort Character::getMaxHP() const {
    return maxHP;
}

ushort Character::getCurrentHP() const {
    return currentHP;
}

char Character::getAbilityScore(Stat stat) const {
    return abilityScores[stat];
}

char Character::getAbilityModifier(Stat stat) const {
    return floor(((float) abilityScores[stat]-10)/2);
}

void Character::addFeat(shared_ptr<Feat> feat) {
    if(feat == nullptr) {
        return;
    }
    feats.push_back(feat);
}

void Character::update(Selecter& selecter, UpdateType uType) {
    level = 0;

    // Calculate HP & level from classes
    if(classes.size() == 0) {
        maxHP = 4;
    } else {
        maxHP = 0;
        for (auto charClass : classes)
        {
            if(charClass != nullptr) {
                maxHP += charClass->getHp();
                level += charClass->getLevel();
            }
        }

        maxHP += (ushort) (this->getAbilityModifier(Constitution) * level);        
    }

    skillProficiencies = getNewSkillVector();
    acModifiers.clear();

    for(int i = 0; i < 6; i++) {
        abilityScores[i] = startingAbilityScores[i];
    }

    for(shared_ptr<Feat> feat: feats) {
        feat->update(*this, selecter, uType);
    }

    currentHP = maxHP;
}

void Character::addAbilityScore(Stat stat, char quantity) {
    abilityScores[stat] += quantity;
}

// Will return false if already proficient in skill
bool Character::addSkillProficiency(Skill skill) {
    // cout << (int) skill << endl;
    // cout << skillProficiencies.size() << endl;
    // int skillIndex = skill;
    // cout << skillIndex << endl;
    if(skillProficiencies[skill].isProficient) {
        return false;
    }
    skillProficiencies[skill].isProficient = true;
    skillProficiencies[skill].bonus.pool[0] += this->proficiencyBonus;
    
    return true;
}

void Character::addSavingThrowProficiency(Stat stat) {
    savingThrowProficiencies[stat] = true;
}

void Character::addArmorProficiency(ArmorType armorType) {
    if (armorType == ArmorType::Clothing)
    {
        return;
    }
    armorProficiencies[armorType] = true;
}

void Character::addWeaponProficiency(WeaponType weaponType) {
    weaponProficiencies[weaponType] = true;
}

void Character::addWeaponProficiency(SingleWeaponProficiency weaponType) {
    if (!isProficient(weaponType))
    {
        singleWeaponProficiencies.push_back(weaponType);
    }    
}

bool Character::addLanguage(string name, bool speak, bool read, bool write) {
    languages.push_back(Language(name, speak, read, write));
    return true;
}

void Character::addRace(Race* race) {
    if (race == nullptr)
    {
        cout << "Bad Race Pointer\n";
        return;
    }
    cout << "Good Race Pointer\n";
    this->race = race;
    race->addTo(*this);
}

void Character::addClass(CharacterClass* charClass) {
    if (charClass == nullptr)
    {
        return;
    }
    
    classes.push_back(charClass);
    charClass->assign(*this);
}

bool Character::isProficient(Skill skill) const {
    return skillProficiencies[skill].isProficient;
}

bool Character::isProficient(ArmorType armorType) const {
    if(armorType == ArmorType::Clothing){return true;};
    return armorProficiencies[armorType];
}

bool Character::isProficient(WeaponType weaponType) const {
    return weaponProficiencies[weaponType];
}

bool Character::isProficient(SingleWeaponProficiency weaponType) const {
    return (find(singleWeaponProficiencies.begin(), singleWeaponProficiencies.end(), weaponType) != singleWeaponProficiencies.end());
}

string Character::toString() const {
    static string statString[6] = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};

    string output = "";

    output += "Name: " + getName() + "\n";

    if(classes.size() == 0) {
        output += "Commoner\n\n";
    } else if(classes.size() == 1) {
        output += classes[0]->getName() +  ' ' + to_string((int) classes[0]->getLevel()) + "\n\n";        
    } else {
        for (int i = 0; i < classes.size(); i++)
        {
            output += classes[i]->getName() +  ' ' + to_string((int) classes[i]->getLevel()) + " / ";    
        }
        output += classes.back()->getName() +  ' ' + to_string((int) classes.back()->getLevel()) + "\n\n";        
    }

    output += "AC: " + to_string(int(getArmorClass())) + '\n';
    output += "HP: " + to_string(getCurrentHP()) + " / " + to_string(getMaxHP()) + '\n';

    for (int i = 0; i < 6; i++)
    {
        output += '\n' + statString[i] + ": " + to_string(int(this->getAbilityScore(Stat(i)))) + "(" + to_string(int(this->getAbilityModifier(Stat(i)))) + ")"; 
    }  

    output += "\n\nSaving Throws";
    for (char s = 0; s < 6; s++)
    {
        output += "\n" + statString[s] + ": " + to_string((int) (getAbilityModifier(Stat{s}) + savingThrowProficiencies[s]*proficiencyBonus));
    }    

    output += "\n\nProficiencies";
    for (char i = 0; i < 18; i++)
    {
        output += '\n' + skillProficiencies[i].toStringWithStat(*this, getDefaultStat((Skill) i));
    }

    output += "\n\nArmor Proficiencies";
    if(armorProficiencies[ArmorType::LightArmor]) {
        output += "\nLight Armor";
    }
    if(armorProficiencies[ArmorType::MediumArmor]) {
        output += "\nMedium Armor";
    }
    if(armorProficiencies[ArmorType::HeavyArmor]) {
        output += "\nHeavy Armor";
    }
    if(armorProficiencies[ArmorType::Shield]) {
        output += "\nShields";
    }


    output += "\n\nWeapon Proficiencies";
    if (weaponProficiencies[WeaponType::Improvised])
    {
        output += "\nImprovised Weapons";
    }
    
    if(weaponProficiencies[WeaponType::SimpleMelee] && weaponProficiencies[WeaponType::SimpleRanged]) {
        output += "\nSimple Weapons";
    } else if(weaponProficiencies[WeaponType::SimpleMelee]) {
        output += "\nSimple Melee Weapons";
    } else if(weaponProficiencies[WeaponType::SimpleRanged]) {
        output += "\nSimple Ranged Weapons";
    }

    if(weaponProficiencies[WeaponType::MartialMelee] && weaponProficiencies[WeaponType::MartialRanged]) {
        output += "\nMartial Weapons";
    } else if(weaponProficiencies[WeaponType::MartialMelee]) {
        output += "\nMartial Melee Weapons";
    } else if(weaponProficiencies[WeaponType::SimpleRanged]) {
        output += "\nMartial Ranged Weapons";
    }

    if (weaponProficiencies[WeaponType::Firearm])
    {
        output += "\nFirearms";
    }
    
    for(auto weaponProf : singleWeaponProficiencies) {
        output += "\n" + weaponProf.name;
    }
    
    for(auto feat : feats) {
        output += "\n\n" + feat->toString();
    }

    return output;
}


vector<Proficiency> Character::getNewSkillVector() {
    vector<Proficiency> skills;
    skills.reserve(18);
    for(char i = Skill::Acrobatics; i <= Skill::Survival; i++) {
        skills.push_back(Proficiency(SKILL_NAME[i]));
    }

    return skills;
}

shared_ptr<Armor> Character::getArmor() const {
    return armor;
}

void Character::addAcModifier(shared_ptr<ArmorClassModifier> modifier) {
    acModifiers.push_back(modifier);
}

void Character::addAcCalculator(shared_ptr<ArmorClassCalculator> calculator) {
    acCalculators.push_back(calculator);
}

void Character::save(ostream& outputStream) {
    outputStream << name << '\n';
    for(int i = 0; i < 6; ++i) {
        outputStream << startingAbilityScores[i];
    }

    outputStream << level;

    if(race != nullptr) {
        cout << "Saving Race\n";
        race->save(outputStream);
    } else {cout << "No Race Exists\n";}

    for(CharacterClass* cClass : classes) {
        cClass->save(outputStream);
    }
}

Character* Character::load(istream& inputStream) {
    string name;
    std::getline(inputStream, name, '\n');
    char abilityScores[6];
    for(int i = 0; i < 6; i++) {
        abilityScores[i] = inputStream.get();
    }

    Character* c = new Character(name, abilityScores);
    c->loaded = true;
    c->level = inputStream.get();

    string sourceString;

    // Load Race
    cout << "Loading Race\n";
    std::getline(inputStream, sourceString, '\n');
    Race* loadedRace = SRD_SOURCE.loadRace(inputStream);
    if(loadedRace == nullptr) {cout << "Loading Race Failed\n";};
    c->addRace(loadedRace);

    // Load Class
    cout << "Loading Class\n";
    std::getline(inputStream, sourceString, '\n');
    CharacterClass* loadedClass = SRD_SOURCE.loadClass(inputStream);
    if(loadedClass == nullptr) {cout << "Loading Class Failed\n";}
    c->addClass(loadedClass);

    // Load Background


    return c;
}