#include <string>

using namespace std;

class Character;

class Feat{
    public:
    virtual string getDescription() = 0;
};

class AbilityScoreFeat : public Feat {
    public:
    virtual void updateAbility(Character* character) = 0;
};