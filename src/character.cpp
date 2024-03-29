#include <string>
#include <vector>
#include "character.hpp"
#include "proficiencies.hpp"
#include "feats.hpp"

Character::Character(string name, char stats[6]){
        
    for(int i = 0; i < 6; ++i) {
        abilityScores[i] = stats[i];
        startingAbilityScores[i] = stats[i];
    }

    this->name = name;
    maxHP = 4;
    currentHP = maxHP;
    speed = 30;
    proficiencyBonus = 2;
}

string Character::getName() {
    return name;
}

char Character::getArmorClass() {
    return 10 + this->getAbilityModifier(Stat::Dexterity);
}

ushort Character::getMaxHP() {
    return maxHP;
}

ushort Character::getCurrentHP()
{
    return currentHP;
}

char Character::getAbilityScore(Stat stat) {
    return abilityScores[stat];
}

char Character::getAbilityModifier(Stat stat) {
    return (abilityScores[stat]-10)/2;
}

void Character::addFeat(shared_ptr<Feat> feat) {
    if(feat == nullptr) {
        return;
    }
    feats.push_back(feat);
    update();
}

void Character::update() {

    skillProficiencies = getNewSkillVector();

    for(int i = 0; i < 6; i++) {
        abilityScores[i] = startingAbilityScores[i];
    }

    for(shared_ptr<Feat> feat: feats) {
        feat->update(*this);
    }
}

void Character::addAbilityScore(Stat stat, char quantity) {
    abilityScores[stat] += quantity;
}

// Will return false if already proficient in skill
bool Character::addSkillProficiency(Skill skill) {
    if(skillProficiencies[skill].isProficient) {
        return false;
    }
    skillProficiencies[skill].isProficient = true;
    skillProficiencies[skill].bonus.pool[0] += this->proficiencyBonus;
    
    return true;
}


bool Character::addLanguage(string name, bool speak, bool read, bool write) {
    languages.push_back(Language(name, speak, read, write));
    return true;
}

void Character::addRace(Race* race) {
    race->addTo(*this);
}

bool Character::isProficient(Skill skill) {
    return skillProficiencies[skill].isProficient;
}

string Character::toString() {
    static string statString[6] = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};

    string output = "";

    output += "Name: " + getName() + "\n\n";
    output += "AC: " + to_string(int(getArmorClass())) + '\n';
    output += "HP: " + to_string(getCurrentHP()) + " / " + to_string(getMaxHP()) + '\n';

    for (int i = 0; i < 6; i++)
    {
        output += '\n' + statString[i] + ": " + to_string(int(this->getAbilityScore(Stat(i)))) + "(" + to_string(int(this->getAbilityModifier(Stat(i)))) + ")"; 
    }  

    output += "\n\nProficiencies";
    for (char i = 0; i < 18; i++)
    {
        output += '\n' + skillProficiencies[i].toStringWithStat(this, getDefaultStat((Skill) i));
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