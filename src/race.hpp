class Feat;

#include "feats.hpp"
#include <memory>

class Character;

class Race {
   virtual bool addTo(Character& character) = 0;
};

class Elf: public Race {
    protected:
    class ElfAbilityIncrease: public AbilityScoreFeat {
        string getDescription() override {return "Elf Ability Increase";};
        void updateAbility(Character* character) override;
    };

    public:
    Elf(Character& character);
    bool addTo(Character& character) override;
};