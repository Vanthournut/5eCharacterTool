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

    // Fey Ancestry
    std::shared_ptr<Feat> feyAncestry (new ElfFeyAncestry());
    feats.push_back(feyAncestry);
    character.addFeat(feyAncestry);

    // Trance
    std::shared_ptr<Feat> trance (new ElfTrance());
    feats.push_back(trance);
    character.addFeat(trance);

    // Languages
    std::shared_ptr<Feat> languages (new ElfLanguages());
    feats.push_back(languages);
    character.addFeat(languages);

    return true;
}

Elf::Elf(Character& character) {
    feats = vector<shared_ptr<Feat>>();
    this->addTo(character);
}

void Elf::ElfAbilityIncrease::update(Character& character) {
    character.addAbilityScore(Stat::Dexterity, 2);
}

void Elf::ElfKeenSense::update(Character& character) {
    character.addSkillProficiency(Skill::Perception);
}

void Elf::ElfFeyAncestry::update(Character& character) {
    
}

void Elf::ElfTrance::update(Character& character) {

}

void Elf::ElfLanguages::update(Character& character) {
    character.addLanguage("Common", true, true, true);
    character.addLanguage("Elvish", true, true, true);
}

HighElf::HighElf(Character& character) : Elf(character) 
{
    this->addTo(character);
}

void HighElf::HighElfAbilityIncrease::update(Character& character) {
    character.addAbilityScore(Stat::Intelligence, 1);
}

void HighElf::HighElfCantrip::update(Character& character) {

}

void HighElf::HighElfExtraLanguage::update(Character& character) {

}

void HighElf::HighElfWeapons::update(Character& character) {

}

bool HighElf::addTo(Character& character) {

    // Ability Score Increase
    std::shared_ptr<Feat> highElfAbilityIncrease (new HighElfAbilityIncrease());
    feats.push_back(highElfAbilityIncrease);
    character.addFeat(highElfAbilityIncrease);

    // Cantrip
    std::shared_ptr<Feat> cantrip (new HighElfCantrip());
    feats.push_back(cantrip);
    character.addFeat(cantrip);

    // Weapons
    std::shared_ptr<Feat> weapons (new HighElfWeapons());
    feats.push_back(weapons);
    character.addFeat(weapons);

    // Language
    std::shared_ptr<Feat> extraLanguage (new HighElfExtraLanguage());
    feats.push_back(extraLanguage);
    character.addFeat(extraLanguage);

    return true;
};