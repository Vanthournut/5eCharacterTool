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
    vector<SkillProficiency> skillProficiencies;

    // Feats
    vector<shared_ptr<Feat>> feats;
    vector<shared_ptr<AbilityScoreFeat>> abilityScoreFeats;

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
    void addFeat(Feat* feat);
    void addAbilityScoreFeat(shared_ptr<AbilityScoreFeat>);
    void add2AbilityScore(Stat stat, char quantity);

    void update();

    Character(string name, char stats[6] = defaultAbilityScores);

};