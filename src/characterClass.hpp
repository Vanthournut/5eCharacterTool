#pragma once

#include "selecter.hpp"
#include "armor.hpp"
#include "feats.hpp"
#include <memory>
#include "proficiencies.hpp"

class CharacterClass {
    protected:
    char level;
    vector<ushort> hpList;
    vector<shared_ptr<Feat>> featList;
    
    public:
    CharacterClass() {hpList = vector<ushort>(); level = 0;}
    virtual string getName() = 0;
    virtual void assignStartingClass(Character& character, Selecter& selecter) = 0;
    virtual void assignMultiClass(Character& character, Selecter& selecter) = 0;
    virtual void levelUp(Character& character, Selecter& selecter) = 0;
    ushort getHp() {ushort hp = 0; for(ushort hpVal : hpList){hp += hpVal;} return hp;}
    char getLevel() {return level;}
};

class Barbarian : public CharacterClass {

private:
    class BarbarianStartingProficiencies : public Feat {        
        public:
        vector<Skill> skillList;
        BarbarianStartingProficiencies() {};
        string getName() const override {return "Barbarian: Starting Proficiencies";};
        string getDescription() const override {return "";};
        void update(Character& character, Selecter& selecter, UpdateType uType) override;
    };

    class BarbarianRage : public Feat {
        private:
        char rages;
        char maxRages;
        char rageDamage;

        public:
        BarbarianRage();
        string getName() const override {return "Barbarian: Rage";};
        string getDescription() const override {return "In battle, you fight with primal ferocity. On your turn, you can enter a rage as a bonus action. \n\n\
While raging, you gain the following benefits if you aren't wearing heavy armor: \n\n\
    - You have advantage on Strength checks and Strength saving throws. \n\
    - When you make a melee weapon attack using Strength, you gain a bonus to the damage roll that increases as you gain levels as a barbarian, as shown in the Rage Damage column of the Barbarian table. \n\
    - You have resistance to bludgeoning, piercing, and slashing damage.\n\n\
If you are able to cast spells, you can't cast them or concentrate on them while raging. \n\n\
Your rage lasts for 1 minute. It ends early if you are knocked unconscious or if your turn ends and you haven't attacked a hostile creature since your last turn or taken damage since then. You can also end your rage on your turn as a bonus action.\n\n\
Once you have raged the number of times shown for your barbarian level in the Rages column of the Barbarian table, you must finish a long rest before you can rage again.";};
        void update(Character& character, Selecter& selecter, UpdateType uType) override;
    };

    class BarbarianUnarmoredDefense : public Feat {
        private:
        class BarbarianUnarmoredDefenseCalculator : public ArmorClassCalculator {
            char calculateArmorClass(Character& character) override;
        };

        public:
        string getName() const override {return "Barbarian: Unarmored Defense";};
        string getDescription() const override {return "While you are not wearing any armor, your Armor Class equals 10 + your Dexterity modifier + your Constitution modifier. You can use a shield and still gain this benefit.";};
        void update(Character& character, Selecter& selecter, UpdateType uType) override;
    };

public:
    Barbarian();
    string getName() override {return "Barbarian";}
    void assignStartingClass(Character& character, Selecter& selecter) override;
    void assignMultiClass(Character& character, Selecter& selecter) override {};
    void levelUp(Character& character, Selecter& selecter) override;
};