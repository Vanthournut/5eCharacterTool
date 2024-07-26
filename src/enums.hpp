#pragma once

static const char* SRD_IDENTIFYING_STRING = "SRD";

namespace SRDEnums {
    enum Type : char {
        Class = 0,
        Subclass,
        Race,
        Background,
        Feat,
        Equipment,
        Spell
    };

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

    enum Races : char {
        HighElf = 0
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
}