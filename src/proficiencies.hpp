#include <string>

using namespace std;

class SavingThrowProficiency {

};

class SkillProficiency {
    enum Skill : char {
        Acrobatics,
        AnimalHandling,
        Arcana,
        Athletics,
        Deception,
        History,
        Insight,
        Intimidation,
        Investigation,
        Medicine,
        Nature,
        Perception,
        Performance,
        Persuasion,
        Religion,
        SleightOfHand,
        Stealth,
        Survival
    };

    Stat getDefaultStat(Skill skill) {
        static const Stat defaultSkillStat[18] = {
            Stat::Dexterity,    // Acrobatics
            Stat::Wisdom,       // Animal Handling
            Stat::Intelligence, // Arcana
            Stat::Strength,     // Athletics
            Stat::Charisma,     // Deception
            Stat::Intelligence, // History
            Stat::Wisdom,       // Insight
            Stat::Charisma,     // Intimidation
            Stat::Intelligence, // Investigation
            Stat::Wisdom,       // Medicine
            Stat::Intelligence, // Natures
            Stat::Wisdom,       // Perception
            Stat::Charisma,     // Persuasion
            Stat::Charisma,     // Performance
            Stat::Intelligence, // Religion
            Stat::Dexterity,    // Sleight Of Hand
            Stat::Dexterity,    // Stealth
            Stat::Wisdom        // Survival
        };

        return defaultSkillStat[skill];
    }
};

class ToolProficiency {

};

class WeaponProficiency {

};