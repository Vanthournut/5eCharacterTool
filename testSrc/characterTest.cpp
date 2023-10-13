#include <catch2/catch_test_macros.hpp>
#include "../src/character.hpp"
#include "../src/race.hpp"

#include <iostream>
#include "../src/spellcasting.hpp"

TEST_CASE("Classless Characters", "[character]") {
    Stat statArray[6] {Stat::Strength, Stat::Dexterity, Stat::Constitution, Stat::Intelligence, Stat::Wisdom, Stat::Charisma};
    
    SECTION("Default Values") {

        ConsoleSelecter selecter;
        vector<SelecterItem*> featList;
        class TestSelecterItem : public SelecterItem {
            string getName() const override {return "Test Name";}
            string getDescription() const override {return "Test Description";}
        };
        TestSelecterItem t1;
        TestSelecterItem t2;
        TestSelecterItem t3;

        featList.push_back(&t1);
        featList.push_back(&t2);
        featList.push_back(&t3);

        //cout << ACID_SPLASH.getName() << endl;

        selecter.select(WIZARD_SPELL_SELECTOR, 2);

        Character c = Character("Default");
        REQUIRE( (int) c.getArmorClass() == 10 );
        REQUIRE( c.getMaxHP() == 4 );
        REQUIRE( c.getCurrentHP() == 4 );
        REQUIRE( c.getName().compare("Default") == 0 );
        for (Stat stat : statArray)
        {
            REQUIRE( c.getAbilityScore(stat) == 10 );
            REQUIRE( c.getAbilityModifier(stat) == 0 );
        }
    };
    
    SECTION("Standard Array") {
        char stats[6] {15, 14, 13, 12, 10, 8};
        char modifiers[6] {2, 2, 1, 1, 0, -1};

        Character c = Character("Standard", stats);
        REQUIRE( (int) c.getArmorClass() == 12 );
        REQUIRE( c.getMaxHP() == 4 );
        REQUIRE( c.getCurrentHP() == 4 );
        REQUIRE( c.getName().compare("Standard") == 0 );
        for (Stat stat : statArray)
        {
            REQUIRE( c.getAbilityScore(stat) == stats[stat] );
            REQUIRE( c.getAbilityModifier(stat) == modifiers[stat] );
        }

        SECTION("Elf w/ Standard") {
            Elf e;
            c.addRace(&e);
            stats[Stat::Dexterity] += 2;
            modifiers[Stat::Dexterity] += 1;

            REQUIRE( (int) c.getArmorClass() == 13 );
            REQUIRE( c.getMaxHP() == 4 );
            REQUIRE( c.getCurrentHP() == 4 );
            REQUIRE( c.getName().compare("Standard") == 0 );

            REQUIRE( c.addSkillProficiency(Skill::Perception) == false );

            for (Stat stat : statArray)
            {
                REQUIRE( c.getAbilityScore(stat) == stats[stat] );
                REQUIRE( c.getAbilityModifier(stat) == modifiers[stat] );
            }

            c.update();

            REQUIRE( (int) c.getArmorClass() == 13 );
            REQUIRE( c.getMaxHP() == 4 );
            REQUIRE( c.getCurrentHP() == 4 );
            REQUIRE( c.getName().compare("Standard") == 0 );

            REQUIRE( c.addSkillProficiency(Skill::Perception) == false );

            for (Stat stat : statArray)
            {
                REQUIRE( c.getAbilityScore(stat) == stats[stat] );
                REQUIRE( c.getAbilityModifier(stat) == modifiers[stat] );
            }
        }

        SECTION("High Elf w/ Standard") {
            HighElf e;
            c.addRace(&e);
            stats[Stat::Dexterity] += 2;
            modifiers[Stat::Dexterity] += 1;
            stats[Stat::Intelligence] += 1;

            REQUIRE( (int) c.getArmorClass() == 13 );
            REQUIRE( c.getMaxHP() == 4 );
            REQUIRE( c.getCurrentHP() == 4 );
            REQUIRE( c.getName().compare("Standard") == 0 );

            REQUIRE( c.addSkillProficiency(Skill::Perception) == false );

            for (Stat stat : statArray)
            {
                REQUIRE( c.getAbilityScore(stat) == stats[stat] );
                REQUIRE( c.getAbilityModifier(stat) == modifiers[stat] );
            }

            c.update();

            REQUIRE( (int) c.getArmorClass() == 13 );
            REQUIRE( c.getMaxHP() == 4 );
            REQUIRE( c.getCurrentHP() == 4 );
            REQUIRE( c.getName().compare("Standard") == 0 );

            REQUIRE( c.addSkillProficiency(Skill::Perception) == false );

            for (Stat stat : statArray)
            {
                REQUIRE( c.getAbilityScore(stat) == stats[stat] );
                REQUIRE( c.getAbilityModifier(stat) == modifiers[stat] );
            }
        }
    }
}