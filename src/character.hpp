#include <string>
#include <vector>
#include <memory>
#include "stat.hpp"
#include "proficiencies.hpp"

class Feat;
class AbilityScoreFeat;

using namespace std;

static char defaultAbilityScores[6] = {10, 10, 10, 10, 10, 10};

class Character {

    private:

    string name;

    // Proficiencies
    bool savingThrowProficiencies[6];
    bool skillProficiencies[18];
    vector<ToolProficiency> toolProficiencies;
    vector<WeaponProficiency> weaponProficiencies;
    vector<Language> languages;
    bool armorProficiencies[4];

    // Feats & Actions
    vector<shared_ptr<Feat>> feats;
    ushort maxHP;
    ushort currentHP;
    char startingAbilityScores[6];
    char abilityScores[6];
    char speed;


    public:
    string getName();
    char getArmorClass();
    ushort getMaxHP();
    ushort getCurrentHP();
    char getAbilityScore(Stat stat);
    char getAbilityModifier(Stat stat);
    void addFeat(shared_ptr<Feat> feat);
    void addAbilityScore(Stat stat, char quantity);
    
    bool addSkillProficiency(Skill skill);
    bool addLanguage(string name, bool speak, bool read, bool write);

    bool isProficient(Skill skill);

    void update();

    Character(string name, char stats[6] = defaultAbilityScores);

};