#include "characterClass.hpp"
#include "character.hpp"
#include "armor.hpp"

void Barbarian::BarbarianUnarmoredDefense::update(Character& character) {
    shared_ptr<ArmorClassCalculator> calculator (new BarbarianUnarmoredDefenseCalculator());
    character.addAcCalculator(calculator);
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

    character.addArmorProficiency(ArmorType::LightArmor);
    character.addArmorProficiency(ArmorType::MediumArmor);
    character.addArmorProficiency(ArmorType::Shield);
};

void Barbarian::levelUp(Character& character) {

}

Barbarian::BarbarianRage::BarbarianRage() {
    rages, maxRages, rageDamage = 2;
}

void Barbarian::BarbarianRage::update(Character& character) {

};

char Barbarian::BarbarianUnarmoredDefense::BarbarianUnarmoredDefenseCalculator::calculateArmorClass(Character& character) {
    char ac = 0;
    
    if (character.getArmor()->getType() == ArmorType::Clothing)
    {
        ac = 10 + character.getAbilityModifier(Dexterity) + character.getAbilityModifier(Constitution);
    }
    
    return ac;
};