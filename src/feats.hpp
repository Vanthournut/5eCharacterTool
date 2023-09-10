#include <string>
#include "selecter.hpp"

using namespace std;

class Character;

class Feat : public SelecterItem{
    public:
    virtual void update(Character& character) = 0;
};