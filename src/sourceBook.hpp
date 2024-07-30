#pragma once
#include <string>
#include <iostream>
#include <map>
#include "characterClass.hpp"
#include "enums.hpp"
#include "spellcasting.hpp"

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

    public:
    SRD() {};
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