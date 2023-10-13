#include "race.hpp"
#include "character.hpp"


Race::Race() {
    feats = vector<shared_ptr<Feat>>();
}

bool Race::addTo(Character& character) {
    for(auto feat : feats) {
        character.addFeat(feat);
    }
    return true;
}

Elf::Elf() {

    // Ability Score Increase
    std::shared_ptr<Feat> abilityIncrease (new ElfAbilityIncrease());
    feats.push_back(abilityIncrease);

    // Keen Sense
    std::shared_ptr<Feat> keenSense (new ElfKeenSense());
    feats.push_back(keenSense);

    // Fey Ancestry
    std::shared_ptr<Feat> feyAncestry (new ElfFeyAncestry());
    feats.push_back(feyAncestry);

    // Trance
    std::shared_ptr<Feat> trance (new ElfTrance());
    feats.push_back(trance);

    // Languages
    std::shared_ptr<Feat> languages (new ElfLanguages());
    feats.push_back(languages);
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

HighElf::HighElf() : Elf() 
{
    // Ability Score Increase
    std::shared_ptr<Feat> highElfAbilityIncrease (new HighElfAbilityIncrease());
    feats.push_back(highElfAbilityIncrease);

    // Cantrip
    std::shared_ptr<Feat> cantrip (new HighElfCantrip());
    feats.push_back(cantrip);

    // Weapons
    std::shared_ptr<Feat> weapons (new HighElfWeapons());
    feats.push_back(weapons);

    // Language
    std::shared_ptr<Feat> extraLanguage (new HighElfExtraLanguage());
    feats.push_back(extraLanguage);
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