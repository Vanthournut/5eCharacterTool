class Feat;

#include "feats.hpp"
#include "spellcasting.hpp"
#include <memory>
#include <vector>

class Character;

class Race : public SelecterItem {
   virtual bool addTo(Character& character) = 0;
};

class Elf : public Race {
    protected :
    vector<shared_ptr<Feat>> feats;

    public:
    Elf(Character& character);
    bool addTo(Character& character) override;
    string getName() const override {return "Elf";}
    string getDescription() const override {return "Is Elf";};

    //protected:
    class ElfAbilityIncrease : public Feat {
        string getName() const override {return "Elf: Ability Score Increase";};
        string getDescription() const override {return "Your Dexterity score increases by 2.";};
        void update(Character& character) override;
    };

    class ElfKeenSense : public Feat {
        string getName() const override {return "Elf: Keen Senses";};
        string getDescription() const override {return "You have proficiency in the Perception skill.";};
        void update(Character& character) override;
    };

    class ElfFeyAncestry : public Feat {
        string getName() const override {return "Elf: Fey Ancestry";};
        string getDescription() const override {return "You have advantage on saving throws against being charmed, and magic can’t put you to sleep.";};
        void update(Character& character) override;
    };

    class ElfTrance : public Feat {
        string getName() const override {return "Elf: Trance";};
        string getDescription() const override {return "Elves don’t need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is \"trance.\") While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep.";};
        void update(Character& character) override;
    };

    class ElfLanguages : public Feat {
        string getName() const override {return "Elf: Languages";};
        string getDescription() const override {return "You can speak, read, and write Common and Elvish. Elvish is fluid, with subtle intonations and intricate grammar. Elven literature is rich and varied, and their songs and poems are famous among other races. Many bards learn their language so they can add Elvish ballads to their repertoires.";};
        void update(Character& character) override;
    };
};

class HighElf : public Elf {
    HighElf(Character& character);
    bool addTo(Character& character) override;


    class HighElfAbilityIncrease : public Feat {
        string getName() const override {return "High Elf: Ability Score Increase";};
        string getDescription() const override {return "Your Intelligence score increases by 1.";};
        void update(Character& character) override;
    };

    class HighElfWeapons : public Feat {
        string getName() const override {return "High Elf: Weapon Training";};
        string getDescription() const override {return "You have proficiency with the longsword, shortsword, shortbow, and longbow.";};
        void update(Character& character) override;
    };

    class HighElfCantrip : public Feat, SpellcastingSource {
        string getName() const override {return "High Elf: Cantrip";};
        string getDescription() const override {return "You know one cantrip of your choice from the wizard spell list. Intelligence is your spellcasting ability for it.";};
        void update(Character& character) override;
    };

    class HighElfExtraLanguage : public Feat {
        string getName() const override {return "High Elf: Extra Language";};
        string getDescription() const override {return "You can speak, read, and write one extra language of your choosing.";};
        void update(Character& character) override;
    };
};