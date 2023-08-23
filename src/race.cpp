#include "race.hpp"
#include "character.hpp"

bool Race::addTo(Character& character) {
    return true;
}

bool Elf::addTo(Character& character) {
    // Ability Score Increase
    std::shared_ptr<Feat> abilityIncrease (new ElfAbilityIncrease());
    feats.push_back(abilityIncrease);
    character.addFeat(abilityIncrease);

    // Keen Sense
    std::shared_ptr<Feat> keenSense (new ElfKeenSense());
    feats.push_back(keenSense);
    character.addFeat(keenSense);

    return true;
}

Elf::Elf(Character& character) {
    feats = vector<shared_ptr<Feat>>();
    this->addTo(character);
}

void Elf::ElfAbilityIncrease::update(Character& character) {
    character.addAbilityScore(Stat::Dexterity, 2);
    character.addAbilityScore(Stat::Intelligence, 1);
}

void Elf::ElfKeenSense::update(Character& character) {
    character.addSkillProficiency(Skill::Perception);
}