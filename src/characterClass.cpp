#include "characterClass.hpp"
#include "character.hpp"
#include "armor.hpp"

void Barbarian::BarbarianUnarmoredDefense::update(Character& character) {
    shared_ptr<ArmorClassModifier> modifier (new BarbarianUnarmoredDefenseModifier());
    character.addAcModifier(modifier);
};

Barbarian::Barbarian() : CharacterClass() {
};

void Barbarian::assignStartingClass(Character& character){
    shared_ptr<Feat> rageFeat (new BarbarianRage());
    shared_ptr<Feat> unarmoredDefense (new BarbarianUnarmoredDefense());

    level = 1;
    hpList.push_back(12);
    character.addClass(this);

    character.addFeat(rageFeat);
    character.addFeat(unarmoredDefense);
};

void Barbarian::levelUp(Character& character) {

}

Barbarian::BarbarianRage::BarbarianRage() {
    rages, maxRages, rageDamage = 2;
}

void Barbarian::BarbarianRage::update(Character& character) {

};

char Barbarian::BarbarianUnarmoredDefense::BarbarianUnarmoredDefenseModifier::modifyArmorClass(Character& character, char ac) {
    if (character.getArmor()->getType() == ArmorType::Clothing)
    {
        ac += character.getAbilityModifier(Constitution);
    }
    
    return ac;
};