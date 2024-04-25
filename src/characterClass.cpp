#include "characterClass.hpp"
#include "character.hpp"
#include "armor.hpp"

void Barbarian::BarbarianUnarmoredDefense::update(Character& character) {
    shared_ptr<ArmorClassCalculator> calculator (new BarbarianUnarmoredDefenseCalculator());
    character.addAcCalculator(calculator);
};

Barbarian::Barbarian() : CharacterClass() {
};

void Barbarian::assignStartingClass(Character& character, Selecter& selecter){
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

    character.addWeaponProficiency(WeaponType::SimpleMelee);
    character.addWeaponProficiency(WeaponType::SimpleRanged);
    character.addWeaponProficiency(WeaponType::MartialMelee);
    character.addWeaponProficiency(WeaponType::MartialRanged);

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

    character.addSkillProficiency(selectableSkills[results[0]]);
    character.addSkillProficiency(selectableSkills[results[1]]);
    cout << SKILL_NAME[selectableSkills[results[0]]] << endl;
    cout << SKILL_NAME[selectableSkills[results[1]]] << endl;

    // TODO
    // Convert additions to feat to allow for proper update
    // Armor/Weapon Profs will need to be reset
};

void Barbarian::levelUp(Character& character, Selecter& selecter) {

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