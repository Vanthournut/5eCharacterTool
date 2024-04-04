#include "armor.hpp"
#include "character.hpp"

char Unarmored::getArmorClass(Character& character) {return 10 + character.getAbilityModifier(Dexterity);};