#include "proficiencies.hpp"
#include "character.hpp"

string Proficiency::toString() const {
    string output = "";
    output += name + ": " + bonus.toString();
    return output;
}

string Proficiency::toStringWithStat(const Character& c, Stat stat) const {
    string output = "";
    DicePool adjusted;
    adjusted = adjusted + this->bonus;
    adjusted.pool[0] += c.getAbilityModifier(stat);
    output = name + "(" + STAT_SHORT[stat] + "): " + adjusted.toString();
    return output;
}