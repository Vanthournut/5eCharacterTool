#include "spellcasting.hpp"

static vector<Spell*> InitWizardSpellList() {
    vector<Spell*> list;
    list.push_back(&ACID_SPLASH);
    list.push_back(&CHILL_TOUCH);
    return list;
}

vector<Spell*> WIZARD_SPELL_LIST = InitWizardSpellList();
vector<SelecterItem*> WIZARD_SPELL_SELECTOR(WIZARD_SPELL_LIST.begin(), WIZARD_SPELL_LIST.end());
