#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "stat.hpp"
#include "selecter.hpp"
#include "time.hpp"
#include "enums.hpp"

using namespace std;

enum SpellSchool : char {
    Abjuration,
    Conjuration,
    Divination,
    Enchantment,
    Evocation,
    Illusion,
    Necromancy,
    Transmutaion
};

enum SpellLevel : char {
    Cantrip,
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Seventh,
    Eighth,
    Nineth
};

struct SpellComponents
{
    bool verbal;
    bool somatic;
    string material;
    int materialCost;
    bool materialConsumed;
};

class Spell : public SelecterItem {
    public:
    virtual SpellSchool getSchool() const = 0;
    virtual SpellLevel getSpellLevel() const = 0;
    virtual TimeDuration getCastingTime() const = 0;
    virtual bool isConcentration() const = 0;
    virtual bool isRitual() const = 0;
    virtual SpellComponents getComponents() const = 0;
    virtual vector<string> getTags() const = 0;
    virtual void save(ostream& o) const {};
    // static Spell* load(istream& i) {return nullptr;};
};

class SpellcastingSource {
    protected:
    char attackBonus;
    char saveDC;
    Stat spellcastingAbilitity;
    vector<Spell*> spells;
};

class SpellSlotSource : public SelecterItem {
    char spellSlots[9];
    virtual void update() = 0;
};

class Spellcasting : public SpellSlotSource {
    float level;
    char spellSlots[9];
    vector<SpellcastingSource> spellcastingSources;
    vector<SpellSlotSource> SpellSlotSources;
    bool innateSpellcaster;

    public:
    void update() override {};
    string getName() const override {return "Spellcasting Spell Slots";};
    string getDescription() const override {return "";};
    bool isSpellcaster() {return innateSpellcaster;};
};

// TODO
// Master vector of spells
// Clone spell to create a new one
// - Will not apply to altered version of spells
// Wrap in container to prevent contamination

class AcidSplash : public Spell {
    public:
    string getName() const override {return "Acid Splash";};
    string getDescription() const  override {return "You hurl a bubble of acid. Choose one creature you can see within range, or choose two creatures you can see within range that are within 5 feet of each other. A target must succeed on a Dexterity saving throw or take 1d6 acid damage.\nThis spell's damage increases by 1d6 when you reach 5th level (2d6), 11th level (3d6), and 17th level (4d6).";};
    SpellSchool getSchool() const override {return SpellSchool::Conjuration;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::AcidSplash;}
    static Spell* load(istream& i) {return new AcidSplash();};
};

static AcidSplash ACID_SPLASH = AcidSplash();

class ChillTouch : public Spell {
    public:
    string getName() const override {return "Chill Touch";};
    string getDescription() const  override {return "You create a ghostly, skeletal hand in the space of a creature within range. Make a ranged spell attack against the creature to assail it with the chill of the grave. On a hit, the target takes 1d8 necrotic damage, and it can't regain hit points until the start of your next turn. Until then, the hand clings to the target.\n\n\
If you hit an undead target, it also has disadvantage on attack rolls against you until the end of your next turn.\n\n\
This spell's damage increases by 1d8 when you reach 5th level (2d8), 11th level (3d8), and 17th level (4d8).";};
    SpellSchool getSchool() const override {return SpellSchool::Necromancy;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::ChillTouch;}
    static Spell* load(istream& i) {return new ChillTouch();};
};

static ChillTouch CHILL_TOUCH = ChillTouch();

class DancingLights : public Spell {
    public:
    string getName() const override {return "Dancing Lights";};
    string getDescription() const  override {return "You create up to four torch-sized lights within range, making them appear as torches, lanterns, or glowing orbs that hover in the air for the duration. You can also combine the four lights into one glowing vaguely humanoid form of Medium size. Whichever form you choose, each light sheds dim light in a 10-foot radius.\n\n\
As a bonus action on your turn, you can move the lights up to 60 feet to a new spot within range. A light must be within 20 feet of another light created by this spell, and a light winks out if it exceeds the spell's range.";};
    SpellSchool getSchool() const override {return SpellSchool::Evocation;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return true;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "a bit of phosphorus or wychwood, or a glowworm", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::DancingLights;}
    static Spell* load(istream& i) {return new DancingLights();};
};

static DancingLights DANCING_LIGHTS = DancingLights();

class FireBolt : public Spell {
    public:
    string getName() const override {return "Fire Bolt";};
    string getDescription() const  override {return "You hurl a mote of fire at a creature or object within range. Make a ranged spell attack against the target. On a hit, the target takes 1d10 fire damage. A flammable object hit by this spell ignites if it isn't being worn or carried.\n\n\
This spell's damage increases by 1d10 when you reach 5th level (2d10), 11th level (3d10), and 17th level (4d10).";};
    SpellSchool getSchool() const override {return SpellSchool::Evocation;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::FireBolt;}
    static Spell* load(istream& i) {return new FireBolt();};
};

static FireBolt FIRE_BOLT = FireBolt();

class Light : public Spell {
    public:
    string getName() const override {return "Light";};
    string getDescription() const  override {return "You touch one object that is no larger than 10 feet in any dimension. Until the spell ends, the object sheds bright light in a 20-foot radius and dim light for an additional 20 feet. The light can be colored as you like. Completely covering the object with something opaque blocks the light. The spell ends if you cast it again or dismiss it as an action.\n\n\
If you target an object held or worn by a hostile creature, that creature must succeed on a Dexterity saving throw to avoid the spell.";};
    SpellSchool getSchool() const override {return SpellSchool::Evocation;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, false, "a firefly or phosphorescent moss", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::Light;}
    static Spell* load(istream& i) {return new Light();};
};

static Light LIGHT = Light();

class MageHand : public Spell {
    public:
    string getName() const override {return "Mage Hand";};
    string getDescription() const  override {return "A spectral, floating hand appears at a point you choose within range. The hand lasts for the duration or until you dismiss it as an action. The hand vanishes if it is ever more than 30 feet away from you or if you cast this spell again.\n\n\
You can use your action to control the hand. You can use the hand to manipulate an object, open an unlocked door or container, stow or retrieve an item from an open container, or pour the contents out of a vial. You can move the hand up to 30 feet each time you use it.\n\n\
The hand can't attack, activate magic items, or carry more than 10 pounds.";};
    SpellSchool getSchool() const override {return SpellSchool::Conjuration;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o)  const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::MageHand;}
    static Spell* load(istream& i) {return new MageHand();};
};

static MageHand MAGE_HAND = MageHand();

class Mending : public Spell {
    public:
    string getName() const override {return "Mending";};
    string getDescription() const  override {return "This spell repairs a single break or tear in an object you touch, such as broken chain link, two halves of a broken key, a torn cloak, or a leaking wineskin. As long as the break or tear is no larger than 1 foot in any dimension, you mend it, leaving no trace of the former damage.\n\n\
This spell can physically repair a magic item or construct, but the spell can't restore magic to such an object.";};
    SpellSchool getSchool() const override {return SpellSchool::Transmutaion;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Minute, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "two lodestones", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::Mending;}
    static Spell* load(istream& i) {return new Mending();};
};

static Mending MENDING = Mending();

class Message : public Spell {
    public:
    string getName() const override {return "Message";};
    string getDescription() const  override {return "You point your finger toward a creature within range and whisper a message. The target (and only the target) hears the message and can reply in a whisper that only you can hear.\n\n\
You can cast this spell through solid objects if you are familiar with the target and know it is beyond the barrier. Magical silence, 1 foot of stone, 1 inch of common metal, a thin sheet of lead, or 3 feet of wood blocks the spell. The spell doesn't have to follow a straight line and can travel freely around corners or through openings.";};
    SpellSchool getSchool() const override {return SpellSchool::Transmutaion;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "a short piece of copper wire", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::Message;}
    static Spell* load(istream& i) {return new Message();};
};

static Message MESSAGE = Message();

class MinorIllusion : public Spell {
    public:
    string getName() const override {return "Minor Illusion";};
    string getDescription() const  override {return "You create a sound or an image of an object within range that lasts for the duration. The illusion also ends if you dismiss it as an action or cast this spell again.\n\n\
If you create a sound, its volume can range from a whisper to a scream. It can be your voice, someone else's voice, a lion's roar, a beating of drums, or any other sound you choose. The sound continues unabated throughout the duration, or you can make discrete sounds at different times before the spell ends.\n\n\
If you create an image of an object—such as a chair, muddy footprints, or a small chest—it must be no larger than a 5-foot cube. The image can't create sound, light, smell, or any other sensory effect. Physical interaction with the image reveals it to be an illusion, because things can pass through it.\n\n\
If a creature uses its action to examine the sound or image, the creature can determine that it is an illusion with a successful Intelligence (Investigation) check against your spell save DC. If a creature discerns the illusion for what it is, the illusion becomes faint to the creature.";};
    SpellSchool getSchool() const override {return SpellSchool::Illusion;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{false, true, "a bit of fleece", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::MinorIllusion;}
    static Spell* load(istream& i) {return new MinorIllusion();};
};

static MinorIllusion MINOR_ILLUSION = MinorIllusion();

class PoisonSpray : public Spell {
    public:
    string getName() const override {return "Poison Spray";};
    string getDescription() const  override {return "You extend your hand toward a creature you can see within range and project a puff of noxious gas from your palm. The creature must succeed on a Constitution saving throw or take 1d12 poison damage.\n\n\
This spell's damage increases by 1d12 when you reach 5th level (2d12), 11th level (3d12), and 17th level (4d12).";};
    SpellSchool getSchool() const override {return SpellSchool::Conjuration;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::PoisonSpray;}
    static Spell* load(istream& i) {return new PoisonSpray();};
};

static PoisonSpray POISON_SPRAY = PoisonSpray();

class Prestidigitation : public Spell {
    public:
    string getName() const override {return "Prestidigitation";};
    string getDescription() const  override {return "This spell is a minor magical trick that novice spellcasters use for practice. You create one of the following magical effects within range:\n\n\
- You create an instantaneous, harmless sensory effect, such as a shower of sparks, a puff of wind, faint musical notes, or an odd odor.\n\
- You instantaneously light or snuff out a candle, a torch, or a small campfire.\n\
- You instantaneously clean or soil an object no larger than 1 cubic foot.\n\
- You chill, warm, or flavor up to 1 cubic foot of nonliving material for 1 hour.\n\
- You make a color, a small mark, or a symbol appear on an object or a surface for 1 hour.\n\
- You create a nonmagical trinket or an illusory image that can fit in your hand and that lasts until the end of your next turn.\n\n\
If you cast this spell multiple times, you can have up to three of its non-instantaneous effects active at a time, and you can dismiss such an effect as an action.";};
    SpellSchool getSchool() const override {return SpellSchool::Transmutaion;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::Prestidigitation;}
    static Spell* load(istream& i) {return new Prestidigitation();};
};

static Prestidigitation PRESTIDIGITATION = Prestidigitation();

class RayOfFrost : public Spell {
    public:
    string getName() const override {return "Ray of Frost";};
    string getDescription() const  override {return "A frigid beam of blue-white light streaks toward a creature within range. Make a ranged spell attack against the target. On a hit, it takes 1d8 cold damage, and its speed is reduced by 10 feet until the start of your next turn.\n\n\
The spell's damage increases by 1d8 when you reach 5th level (2d8), 11th level (3d8), and 17th level (4d8).";};
    SpellSchool getSchool() const override {return SpellSchool::Evocation;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::RayOfFrost;}
    static Spell* load(istream& i) {return new RayOfFrost();};
};

static RayOfFrost RAY_OF_FROST = RayOfFrost();

class ShockingGrasp : public Spell {
    public:
    string getName() const override {return "Shocking Grasp";};
    string getDescription() const  override {return "Lightning springs from your hand to deliver a shock to a creature you try to touch. Make a melee spell attack against the target. You have advantage on the attack roll if the target is wearing armor made of metal. On a hit, the target takes 1d8 lightning damage, and it can't take reactions until the start of its next turn.\n\n\
The spell's damage increases by 1d8 when you reach 5th level (2d8), 11th level (3d8), and 17th level (4d8).";};
    SpellSchool getSchool() const override {return SpellSchool::Evocation;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return false;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{true, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::ShockingGrasp;}
    static Spell* load(istream& i) {return new ShockingGrasp();};
};

static ShockingGrasp SHOCKING_GRASP = ShockingGrasp();

class TrueStrike : public Spell {
    public:
    string getName() const override {return "True Strike";};
    string getDescription() const  override {return "You extend your hand and point a finger at a target in range. Your magic grants you a brief insight into the target's defenses. On your next turn, you gain advantage on your first attack roll against the target, provided that this spell hasn't ended.";};
    SpellSchool getSchool() const override {return SpellSchool::Divination;};
    SpellLevel getSpellLevel() const override {return SpellLevel::Cantrip;};
    TimeDuration getCastingTime() const override {return TimeDuration{TimeMeasurement::Action, 1};};
    bool isConcentration() const override {return true;};
    bool isRitual() const override {return false;};
    SpellComponents getComponents() const override {return SpellComponents{false, true, "", false};};
    vector<string> getTags() const override {return vector<string>();};
    void save(ostream& o) const override {o << SRD_IDENTIFYING_STRING << '\n' << Cantrip << SRDEnums::TrueStrike;}
    static Spell* load(istream& i) {return new TrueStrike();};
};

static TrueStrike TRUE_STRIKE = TrueStrike();

extern vector<Spell*> WIZARD_SPELL_LIST;
extern vector<SelecterItem*> WIZARD_SPELL_SELECTOR;