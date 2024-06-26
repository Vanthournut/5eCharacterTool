#include "characterClass.hpp"
#include "character.hpp"
#include "armor.hpp"
#include "sourceBook.hpp"

void CharacterClass::assign(Character& character) {
    for(shared_ptr<Feat> feat : featList) {
        character.addFeat(feat);
    }
}

void Barbarian::BarbarianUnarmoredDefense::update(Character& character, Selecter& selecter, UpdateType uType) {
    shared_ptr<ArmorClassCalculator> calculator (new BarbarianUnarmoredDefenseCalculator());
    character.addAcCalculator(calculator);
};

Barbarian::Barbarian(Character& character, Selecter& selecter, bool isStartingClass) : CharacterClass(character, selecter, isStartingClass) {
    isStartingClass? this->createStartingClass(character, selecter) : this->createMultiClass(character, selecter);
};

void Barbarian::createStartingClass(Character& character, Selecter& selecter){

    character.update(selecter, UpdateType::Refresh);

    level = 1;
    hpList.push_back(12);
    isStartingClass = true;

    static vector<Skill> startingSkillList{Skill::AnimalHandling, Skill::Athletics, Skill::Intimidation, Skill::Nature, Skill::Perception, Skill::Survival};

    vector<SelecterItem*> skillSelecterItems;
    vector<Skill> selectableSkills;
    for (Skill skill : startingSkillList) {
        if (!character.isProficient(skill))
        {
            skillSelecterItems.push_back(new SkillSelecterItem(skill));
            selectableSkills.push_back(skill);
        }        
    }

    auto results = selecter.select(skillSelecterItems, 2);

    for(auto s : skillSelecterItems) {
        delete s;
    }

    if(results.size() == 0) {
        return;
    }

    BarbarianStartingProficiencies* startingProficiencies = new BarbarianStartingProficiencies();
    startingProficiencies->skillList.push_back(selectableSkills[results[0]]);
    startingProficiencies->skillList.push_back(selectableSkills[results[1]]);
    featList.push_back(shared_ptr<Feat>(startingProficiencies));

    shared_ptr<Feat> rageFeat (new BarbarianRage());
    shared_ptr<Feat> unarmoredDefense (new BarbarianUnarmoredDefense());

    featList.push_back(rageFeat);
    featList.push_back(unarmoredDefense);

    character.addClass(this);

    return;
};

void Barbarian::levelUp(Character& character, Selecter& selecter) {

}

void Barbarian::BarbarianStartingProficiencies::update(Character& character, Selecter& selecter, UpdateType uType) {
    // Armor Proficiencies
    character.addArmorProficiency(ArmorType::LightArmor);
    character.addArmorProficiency(ArmorType::MediumArmor);
    character.addArmorProficiency(ArmorType::Shield);

    // Weapon Proficiencies
    character.addWeaponProficiency(WeaponType::SimpleMelee);
    character.addWeaponProficiency(WeaponType::SimpleRanged);
    character.addWeaponProficiency(WeaponType::MartialMelee);
    character.addWeaponProficiency(WeaponType::MartialRanged);

    // Skill Proficiencies
    for(Skill skill : skillList) {
        character.addSkillProficiency(skill);
    }

    // Saving Throws
    character.addSavingThrowProficiency(Stat::Strength);
    character.addSavingThrowProficiency(Stat::Constitution);
}

void Barbarian::BarbarianRage::update(Character& character, Selecter& selecter, UpdateType uType) {

};

char Barbarian::BarbarianUnarmoredDefense::BarbarianUnarmoredDefenseCalculator::calculateArmorClass(const Character& character) {
    char ac = 0;
    
    if (character.getArmor()->getType() == ArmorType::Clothing)
    {
        ac = 10 + character.getAbilityModifier(Dexterity) + character.getAbilityModifier(Constitution);
    }
    
    return ac;
};

void Barbarian::save(ostream& o) {
    o << SRD_IDENTIFYING_STRING << '\n';
    o << SRDEnums::Barbarian;
    o << isStartingClass;
    o << level;
    for(char hp : hpList) {
        cout << hp << endl;
        o << hp;
    }
    for(shared_ptr<Feat> feat : featList) {
        feat->save(o);
    }
};

CharacterClass* Barbarian::load(istream& i) {
    Barbarian* barb = new Barbarian();
    barb->isStartingClass = i.get();
    barb->level = i.get();

    char hp;
    for(char l = 0; l < barb->level; l++) {
        hp = i.get();
        barb->hpList.push_back(hp);
    }

    if(barb->isStartingClass) {
        BarbarianStartingProficiencies* startingProficiencies = new BarbarianStartingProficiencies();
        char selectedSkill = i.get();
        startingProficiencies->skillList.push_back((Skill) selectedSkill);
        selectedSkill = i.get();
        startingProficiencies->skillList.push_back((Skill) selectedSkill);
        barb->featList.push_back(shared_ptr<Feat>(startingProficiencies));
    }

    char rages = i.get();
    char maxRages = i.get();
    char rageDamage = i.get();

    shared_ptr<Feat> rageFeat (new BarbarianRage());
    shared_ptr<Feat> unarmoredDefense (new BarbarianUnarmoredDefense());

    barb->featList.push_back(rageFeat);
    barb->featList.push_back(unarmoredDefense);

    return barb;
};