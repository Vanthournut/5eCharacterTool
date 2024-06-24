#include "armor.hpp"
#include "character.hpp"

char Unarmored::getArmorClass(const Character& character) {return 10 + character.getAbilityModifier(Dexterity);};