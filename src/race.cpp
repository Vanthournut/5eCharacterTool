#include "race.hpp"
#include "character.hpp"

bool Race::addTo(Character& character) {
    return true;
}

bool Elf::addTo(Character& character) {
    // character.addFeat(this);
    std::shared_ptr<AbilityScoreFeat> abilityIncrease (new ElfAbilityIncrease());
    character.addAbilityScoreFeat(abilityIncrease);
    return true;
}

Elf::Elf(Character& character) {
    this->addTo(character);
}

/*
std::string Elf::getDescription() {
    return "Elf";
}

void Elf::updateAbility(Character* character) {
    printf("Adding 2 to Dex, 1 to Int\n");
    character->add2AbilityScore(Stat::Dexterity, 2);
    character->add2AbilityScore(Stat::Intelligence, 1);
}
*/

void Elf::ElfAbilityIncrease::updateAbility(Character* character) {
    printf("Adding 2 to Dex, 1 to Int\n");
    character->add2AbilityScore(Stat::Dexterity, 2);
    character->add2AbilityScore(Stat::Intelligence, 1);
}