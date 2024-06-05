#pragma once
#include <string>
#include <iostream>

using namespace std;

class SourceBook {
    public:
    Race* loadRace(istream i) {return nullptr;};
    CharacterClass* loadClass(istream i) {return nullptr;};
    Spell* loadSpell(istream i) {return nullptr;};
    Feat* loadFeat(istream i) {return nullptr;};
    virtual bool isSource(const string& sourceIdentifier) = 0;
};

static const char* SRD_IDENTIFYING_STRING = "SRD";

class SRD : public SourceBook {
    public:
    bool isSource(const string& sourceIdentifier) override {return sourceIdentifier == SRD_IDENTIFYING_STRING;};
};