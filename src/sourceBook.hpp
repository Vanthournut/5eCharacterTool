#pragma once
#include <string>
#include <iostream>
#include <map>
#include "characterClass.hpp"
#include "enums.hpp"

using namespace std;

class SourceBook {
    public:
    virtual Race* loadRace(istream& i) const = 0;
    virtual CharacterClass* loadClass(istream& i) const = 0;
    virtual Spell* loadSpell(istream& i) const = 0;
    virtual Feat* loadFeat(istream& i) const = 0;
    virtual bool isSource(const string& sourceIdentifier) const = 0;
};

class SRD : public SourceBook {
    public:
    SRD() {};
    Race* loadRace(istream& i) const override {return nullptr;};
    CharacterClass* loadClass(istream& i) const override {
        char loadedClass = i.get();
        if((SRDEnums::Classes) loadedClass == SRDEnums::Barbarian) {return Barbarian::load(i);}
        return nullptr;
    };
    Spell* loadSpell(istream& i) const override {return nullptr;};
    Feat* loadFeat(istream& i) const override {return nullptr;};
    bool isSource(const string& sourceIdentifier) const override {return sourceIdentifier == SRD_IDENTIFYING_STRING;};
    
};

static const SRD SRD_SOURCE;