#include <string>
#include <vector>
#include "character.hpp"


Character::Character(string name, char stats[6]){
        
    for(int i = 0; i < 6; ++i) {
        statScores[i] = stats[i];
    }

    this->name = name;
    armorClass = 10 + this->getStatModifier(Stat::Dexterity);
    maxHP = 4;
    currentHP = maxHP;
}

string Character::getName() {
    return name;
}

char Character::getArmorClass() {
    return armorClass;
}

ushort Character::getMaxHP() {
    return maxHP;
}

ushort Character::getCurrentHP()
{
    return currentHP;
}

char Character::getStatScore(Stat stat) {
    return statScores[stat];
}

char Character::getStatModifier(Stat stat) {
    return (statScores[stat]-10)/2;
}