#include "proficiencies.hpp"
#include "character.hpp"

string Proficiency::toString() {
    string output = "";
    output += name + ": " + bonus.toString();
    return output;
}

string Proficiency::toStringWithStat(Character* c, Stat stat) {
    if(c == nullptr) {
        return this->toString();
    }

    string output = "";
    DicePool adjusted;
    adjusted = adjusted + this->bonus;
    adjusted.pool[0] += c->getAbilityModifier(stat);
    output = name + "(" + STAT_SHORT[stat] + "): " + adjusted.toString();
    return output;
}