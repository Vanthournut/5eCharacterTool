#include "race.hpp"
#include "character.hpp"
#include "selecter.hpp"
#include "spellcasting.hpp"
#include "enums.hpp"

Race::Race() {
    feats = vector<shared_ptr<Feat>>();
}

Race::Race(Selecter& selecter) {
    feats = vector<shared_ptr<Feat>>();
}

bool Race::addTo(Character& character) {
    for(auto feat : feats) {
        character.addFeat(feat);
    }
    return true;
}

Elf::Elf() : Race() {

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

Elf::Elf(Selecter& selecter) : Race(selecter) {

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

void Elf::ElfAbilityIncrease::update(Character& character, Selecter& selecter, UpdateType uType) {
    character.addAbilityScore(Stat::Dexterity, 2);
}

void Elf::ElfKeenSense::update(Character& character, Selecter& selecter, UpdateType uType) {
    character.addSkillProficiency(Skill::Perception);
}

void Elf::ElfFeyAncestry::update(Character& character, Selecter& selecter, UpdateType uType) {
    
}

void Elf::ElfTrance::update(Character& character, Selecter& selecter, UpdateType uType) {

}

void Elf::ElfLanguages::update(Character& character, Selecter& selecter, UpdateType uType) {
    character.addLanguage("Common", true, true, true);
    character.addLanguage("Elvish", true, true, true);
}

HighElf::HighElf(Selecter& selecter) : Elf(selecter) 
{
    // Ability Score Increase
    std::shared_ptr<Feat> highElfAbilityIncrease (new HighElfAbilityIncrease());
    feats.push_back(highElfAbilityIncrease);

    auto selection = selecter.select(WIZARD_SPELL_SELECTOR);
    
    if (selection.size() == 0)
    {
        throw exception();
    }
    
    Spell* spell = WIZARD_SPELL_LIST.at(selection[0])->copy();

    // Cantrip
    std::shared_ptr<Feat> cantrip (new HighElfCantrip(spell));
    feats.push_back(cantrip);

    // Weapons
    std::shared_ptr<Feat> weapons (new HighElfWeapons());
    feats.push_back(weapons);

    // Language
    std::shared_ptr<Feat> extraLanguage (new HighElfExtraLanguage());
    feats.push_back(extraLanguage);
}

void HighElf::HighElfAbilityIncrease::update(Character& character, Selecter& selecter, UpdateType uType) {
    character.addAbilityScore(Stat::Intelligence, 1);
}

HighElf::HighElfCantrip::HighElfCantrip(Spell* spell) {
    if (!spell)
    {
        throw exception();
    }
    
    this->spells.push_back(spell);
    this->spellcastingAbilitity = Intelligence;
}

void HighElf::HighElfCantrip::update(Character& character, Selecter& selecter, UpdateType uType) {
    attackBonus = character.getAbilityModifier(Intelligence);
    saveDC = 8 + character.getAbilityModifier(Intelligence);
}

void HighElf::HighElfCantrip::save(ostream& o) {
    cout << spells.front()->getName() << endl;
    spells.front()->save(o);
};

void HighElf::HighElfExtraLanguage::update(Character& character, Selecter& selecter, UpdateType uType) {

}

void HighElf::HighElfWeapons::update(Character& character, Selecter& selecter, UpdateType uType) {
    character.addWeaponProficiency(SingleWeaponProficiency("Longsword"));
    character.addWeaponProficiency(SingleWeaponProficiency("Shortsword"));
    character.addWeaponProficiency(SingleWeaponProficiency("Shortbow"));
    character.addWeaponProficiency(SingleWeaponProficiency("Longbow"));
}

void HighElf::save(ostream& o) {
    cout << "Saving High Elf\n";
    o << SRD_IDENTIFYING_STRING << '\n';
    // o << SRDEnums::Type::Race;
    o << SRDEnums::Races::HighElf;
    for(auto feat : feats) {
        feat->save(o);
    }
}

Race* HighElf::load(istream& i) {
    cout << "Loading High Elf\n";
    HighElf* r = new HighElf();

    // Ability Score Increase
    std::shared_ptr<Feat> highElfAbilityIncrease (new HighElfAbilityIncrease());
    r->feats.push_back(highElfAbilityIncrease);

    // Cantrip
    string sourceStringPlaceholder;
    getline(i, sourceStringPlaceholder);
    Spell* loadedSpell = SRD_SOURCE.loadSpell(i);
    std::shared_ptr<Feat> cantrip (new HighElfCantrip(loadedSpell));
    r->feats.push_back(cantrip);

    // Weapons
    std::shared_ptr<Feat> weapons (new HighElfWeapons());
    r->feats.push_back(weapons);

    // Language
    std::shared_ptr<Feat> extraLanguage (new HighElfExtraLanguage());
    r->feats.push_back(extraLanguage);

    return r;
}