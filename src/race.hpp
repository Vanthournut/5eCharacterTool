class Feat;

#include "feats.hpp"
#include <memory>
#include <vector>

class Character;

class Race {
   virtual bool addTo(Character& character) = 0;
};

class Elf : public Race {
    private :
    vector<shared_ptr<Feat>> feats;

    public:
    Elf(Character& character);
    bool addTo(Character& character) override;

    protected:
    class ElfAbilityIncrease : public Feat {
        string getName() override {return "Elf: Ability Score Increase";};
        string getDescription() override {return "Your Dexterity score increases by 2.";};
        void update(Character& character) override;
    };

    class ElfKeenSense : public Feat {
        string getName() override {return "Elf: Keen Senses";};
        string getDescription() override {return "You have proficiency in the Perception skill.";};
        void update(Character& character) override;
    };
};