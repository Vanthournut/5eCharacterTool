#include <string>

using namespace std;

class Character;

class Feat{
    public:
    virtual string getName() = 0;
    virtual string getDescription() = 0;
    virtual void update(Character& character) = 0;
};