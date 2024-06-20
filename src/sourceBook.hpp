#pragma once
#include <string>
#include <iostream>
#include <map>

using namespace std;

class SourceBook {
    public:
    virtual Race* loadRace(istream i) = 0;
    virtual CharacterClass* loadClass(istream i) = 0;
    virtual Spell* loadSpell(istream i) = 0;
    virtual Feat* loadFeat(istream i) = 0;
    virtual bool isSource(const string& sourceIdentifier) = 0;
};

static const char* SRD_IDENTIFYING_STRING = "SRD";

class SRD : public SourceBook {

    public:
    bool isSource(const string& sourceIdentifier) override {return sourceIdentifier == SRD_IDENTIFYING_STRING;};

    enum Classes : char {
        Barbarian = 0,
        Bard,
        Cleric,
        Druid,
        Fighter,
        Monk,
        Paladin,
        Ranger,
        Rogue,
        Sorcerer,
        Warlock,
        Wizard
    };

    enum Cantrips : char {
        AcidSplash = 0,
        ChillTouch,
        DancingLights,
        Druidcraft,
        EldritchBlast,
        FireBolt,
        Guidance,
        Light,
        MageHand,
        Mending,
        Message,
        MinorIllusion,
        PoisonSpray,
        Prestidigitation,
        ProduceFlame,
        RayOfFrost,
        Resistance,
        SacredFlame,
        Shillelagh,
        ShockingGrasp,
        SpareTheDying,
        Thaumaturgy,
        TrueStrike,
        ViciousMockery
    };
};