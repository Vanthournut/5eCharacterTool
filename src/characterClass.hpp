#pragma once

#include "selecter.hpp"
#include "armor.hpp"
#include "feats.hpp"

class Barbarian {

private:
    char rages;
    char maxRages;
    char rageDamage;

    class BarbarianRage : public Feat {
        string getName() const override {return "Barbarian: Rage";};
        string getDescription() const override {return "In battle, you fight with primal ferocity. On your turn, you can enter a rage as a bonus action. \n\n\
While raging, you gain the following benefits if you aren't wearing heavy armor: \n\n\
    - You have advantage on Strength checks and Strength saving throws. \n\
    - When you make a melee weapon attack using Strength, you gain a bonus to the damage roll that increases as you gain levels as a barbarian, as shown in the Rage Damage column of the Barbarian table. \n\
    - You have resistance to bludgeoning, piercing, and slashing damage.\n\n\
If you are able to cast spells, you can't cast them or concentrate on them while raging. \n\n\
Your rage lasts for 1 minute. It ends early if you are knocked unconscious or if your turn ends and you haven't attacked a hostile creature since your last turn or taken damage since then. You can also end your rage on your turn as a bonus action.\n\n\
Once you have raged the number of times shown for your barbarian level in the Rages column of the Barbarian table, you must finish a long rest before you can rage again.";};
        void update(Character& character) override;
    };

    class BarbarianUnarmoredDefense : public Feat {
        private:
        class BarbarianUnarmoredDefenseModifier : public ArmorClassModifier {
            char modifyArmorClass(Character& character, char ac) override;
        };

        public:
        string getName() const override {return "Barbarian: Unarmored Defense";};
        string getDescription() const override {return "While you are not wearing any armor, your Armor Class equals 10 + your Dexterity modifier + your Constitution modifier. You can use a shield and still gain this benefit.";};
        void update(Character& character) override;
    };

public:
    Barbarian();
    void assignStartingClass(Character& character);

};