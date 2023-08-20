#include <string>
#include <vector>
#include "character.hpp"

#include "feats.hpp"

Character::Character(string name, char stats[6]){
        
    for(int i = 0; i < 6; ++i) {
        abilityScores[i] = stats[i];
        startingAbilityScores[i] = stats[i];
    }

    this->name = name;
    maxHP = 4;
    currentHP = maxHP;
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

void Character::addFeat(Feat* feat) {
    //feats.push_back(make_shared<Feat>(*feat));
}

void Character::addAbilityScoreFeat(shared_ptr<AbilityScoreFeat> feat) {
    abilityScoreFeats.push_back(feat);
    update();
}

void Character::update() {

    for(int i = 0; i < 6; i++) {
        abilityScores[i] = startingAbilityScores[i];
    }

    for(shared_ptr<AbilityScoreFeat> feat: abilityScoreFeats) {
        printf("Updating Ability Feat %s\n", feat->getDescription().c_str());
        feat->updateAbility(this);
    }
}

void Character::add2AbilityScore(Stat stat, char quantity) {
    abilityScores[stat] += quantity;
}