#pragma once
#include <string>
#include <iostream>
#include <map>
#include "characterClass.hpp"
#include "enums.hpp"
#include "spellcasting.hpp"
#include <algorithm>

using namespace std;

class SourceBook {
    private:
    const map<char, Spell*(*)(istream&)> spellFactory[10];
    const map<string, vector<Spell*>> spellLists;
    const vector<CharacterClass> classes;

    public:
    virtual string getSourceId() const = 0;
    virtual Race* loadRace(istream& i) const = 0;
    virtual CharacterClass* loadClass(istream& i) const = 0;
    virtual Spell* loadSpell(istream& i) const = 0;
    virtual Feat* loadFeat(istream& i) const = 0;
    virtual bool isSource(const string& sourceIdentifier) const = 0;
    // Get Spells from list
    template <class Predicate>
    void getSpellList(string listName, vector<Spell*>& returnVector, Predicate predicate = nullptr) const {
        auto it = spellLists.find(listName);
        if (it == spellLists.end()) return;
        if (predicate == nullptr) {
            returnVector.insert(returnVector.end(), it->second.begin(), it->second.end());
        } else {
            for(auto spell : it->second) {
                if(predicate(spell)) {
                    returnVector.push_back(spell);
                }
            }
        }
    };
    // void getRaces() {};
    // void getClasses() {};
    // Get Feats from list
};

class SourceBookManager {
    vector<SourceBook*> sourceBooks;
    public:

    SourceBook* getSourceBook(const string& sourceIdentifier) const {
        for(auto source : sourceBooks) {
            if(source) {
                if(source->isSource(sourceIdentifier)) {
                    return source;
                }
            }
        }
        return nullptr;
    };

    Race* loadRace(istream& i) const {
        Race* loadedRace = nullptr;
        for(auto source : sourceBooks) {
            if(source) {
                loadedRace = source->loadRace(i);
            }
            if(loadedRace) {
                return loadedRace;
            }
        }
        return nullptr;
    };
    CharacterClass* loadClass(istream& i) const {
        CharacterClass* loadedClass = nullptr;
        for(auto source : sourceBooks) {
            if(source) {
                loadedClass = source->loadClass(i);
            }
            if(loadedClass) {
                return loadedClass;
            }
        }
        return nullptr;
    };
    Spell* loadSpell(istream& i) const {
        Spell* loadedSpell = nullptr;
        for(auto source : sourceBooks) {
            if(source) {
                loadedSpell = source->loadSpell(i);
            }
            if(loadedSpell) {
                return loadedSpell;
            }
        }
        return nullptr;
    };
    Feat* loadFeat(istream& i) const {
        Feat* loadedFeat = nullptr;
        for(auto source : sourceBooks) {
            if(source) {
                loadedFeat = source->loadFeat(i);
            }
            if(loadedFeat) {
                return loadedFeat;
            }
        }
        return nullptr;
    };
    // virtual bool isSource(const string& sourceIdentifier) const = 0;
    // Get Spells from list
    template <class Predicate>
    void getSpellList(string listName, vector<Spell*>& returnVector, Predicate predicate = nullptr) const {
        for(auto source : sourceBooks) {
            if(source) {
                source->getSpellList(listName, returnVector, predicate);
            }
        }
    };
    // void getRaces() {};
    // void getClasses() {};
    // Get Feats from list
    void addSourceBook(SourceBook* source) {
        if(source) {
            if(!getSourceBook(source->getSourceId())) {
                sourceBooks.push_back(source);
            }
        }
    };
    void removeSourceBook(string& sourceID) {
        for(auto it = sourceBooks.begin(); it != sourceBooks.end(); it++) {
            if((*it)->isSource(sourceID)) {
                delete *it;
                sourceBooks.erase(it);
                return;
            }
        }
    }
};

class SRD : public SourceBook {
    private:
    const map<char, Spell*(*)(istream&)> spellFactory[10] = {
        { // Cantrips
            {SRDEnums::AcidSplash, AcidSplash::load},
            {SRDEnums::ChillTouch, ChillTouch::load},
            {SRDEnums::DancingLights, DancingLights::load},
            // {SRDEnums::Druidcraft, Druidcraft::load},
            // {SRDEnums::EldritchBlast, EldritchBlast::load},
            {SRDEnums::FireBolt, FireBolt::load},
            // {SRDEnums::Guidance, Guidance::load},
            {SRDEnums::Light, Light::load},
            {SRDEnums::MageHand, MageHand::load},
            {SRDEnums::Mending, Mending::load},
            {SRDEnums::Message, Message::load},
            {SRDEnums::MinorIllusion, MinorIllusion::load},
            {SRDEnums::PoisonSpray, PoisonSpray::load},
            {SRDEnums::Prestidigitation, Prestidigitation::load},
            // {SRDEnums::ProduceFlame, ProduceFlame::load},
            {SRDEnums::RayOfFrost, RayOfFrost::load},
            // {SRDEnums::Resistance, Resistance::load},
            // {SRDEnums::SacredFlame, SacredFlame::load},
            // {SRDEnums::Shillelagh, Shillelagh::load},
            {SRDEnums::ShockingGrasp, ShockingGrasp::load},
            // {SRDEnums::SpareTheDying, SpareTheDying::load},
            // {SRDEnums::Thaumaturgy, Thaumaturgy::load},
            {SRDEnums::TrueStrike, TrueStrike::load}
            // {SRDEnums::ViciousMockery, ViciousMockery::load}
        }
    };

    const map<string, vector<Spell*>> spellLists = {
        {
            "Wizard", 
            {{
                &ACID_SPLASH, &CHILL_TOUCH, &DANCING_LIGHTS, &FIRE_BOLT, &LIGHT, &MAGE_HAND, &MENDING, &MESSAGE, &MINOR_ILLUSION, &POISON_SPRAY, &PRESTIDIGITATION, &RAY_OF_FROST, &SHOCKING_GRASP, &TRUE_STRIKE
            }}
        }
    };

    public:
    SRD() {};
    string getSourceId() const override {return SRD_IDENTIFYING_STRING;};
    Race* loadRace(istream& i) const override {
        char loadedRace = i.get();
        if (loadedRace == SRDEnums::HighElf)
        {
            return HighElf::load(i);
        }
        
        return nullptr;
    };
    CharacterClass* loadClass(istream& i) const override {
        char loadedClass = i.get();
        if(loadedClass == SRDEnums::Barbarian) {return Barbarian::load(i);}
        return nullptr;
    };
    Spell* loadSpell(istream& i) const override {
        char spellLevel = i.get();
        char spellEnum = i.get();
        cout << (int) spellLevel << endl;
        cout << (int) spellEnum << endl;
        if (spellLevel > SpellLevel::Nineth || spellFactory[spellLevel].find(spellEnum) == spellFactory[spellLevel].end())
        {
            return nullptr;
        }
        cout << "Spell Loaded\n";
        return spellFactory[spellLevel].find(spellEnum)->second(i);
    };
    Feat* loadFeat(istream& i) const override {return nullptr;};
    bool isSource(const string& sourceIdentifier) const override {return sourceIdentifier == SRD_IDENTIFYING_STRING;};    
};

static const SRD SRD_SOURCE;