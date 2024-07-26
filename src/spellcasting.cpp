#include "spellcasting.hpp"

static vector<Spell*> InitWizardSpellList() {
    vector<Spell*> list;
    list.push_back(&ACID_SPLASH);
    list.push_back(&CHILL_TOUCH);
    list.push_back(&DANCING_LIGHTS);
    list.push_back(&FIRE_BOLT);
    list.push_back(&LIGHT);
    list.push_back(&MAGE_HAND);
    list.push_back(&MENDING);
    list.push_back(&MESSAGE);
    list.push_back(&MINOR_ILLUSION);
    list.push_back(&POISON_SPRAY);
    list.push_back(&PRESTIDIGITATION);
    list.push_back(&RAY_OF_FROST);
    list.push_back(&SHOCKING_GRASP);
    list.push_back(&TRUE_STRIKE);
    return list;
}

vector<Spell*> WIZARD_SPELL_LIST = InitWizardSpellList();
vector<SelecterItem*> WIZARD_SPELL_SELECTOR(WIZARD_SPELL_LIST.begin(), WIZARD_SPELL_LIST.end());