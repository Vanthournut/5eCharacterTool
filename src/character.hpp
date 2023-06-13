#include <string>
#include <vector>
#include "stat.hpp"

using namespace std;

static char defaultStats[6] = {10, 10, 10, 10, 10, 10};

class Character {

    private:

    string name;
    char armorClass;
    ushort maxHP;
    ushort currentHP;
    char statScores[6];

    public:
    string getName();
    char getArmorClass();
    ushort getMaxHP();
    ushort getCurrentHP();
    char getStatScore(Stat stat);
    char getStatModifier(Stat stat);

    Character(string name, char stats[6] = defaultStats);

};