#include <catch2/catch_test_macros.hpp>
#include "../src/character.hpp"

TEST_CASE("Classless Characters", "[character]") {
    Stat statArray[6] {Stat::Strength, Stat::Dexterity, Stat::Constitution, Stat::Intelligence, Stat::Wisdom, Stat::Charisma};
    
    SECTION("Default Values") {
        Character c = Character("Default");
        REQUIRE( c.getArmorClass() == 10 );
        REQUIRE( c.getMaxHP() == 4 );
        REQUIRE( c.getCurrentHP() == 4 );
        REQUIRE( c.getName().compare("Default") == 0 );
        for (Stat stat : statArray)
        {
            REQUIRE( c.getStatScore(stat) == 10 );
            REQUIRE( c.getStatModifier(stat) == 0 );
        }
    };
    
    SECTION("Standard Array") {
        char stats[6] {15, 14, 13, 12, 10, 8};
        char modifiers[6] {2, 2, 1, 1, 0, -1};

        Character c = Character("Standard", stats);
        REQUIRE( c.getArmorClass() == 12 );
        REQUIRE( c.getMaxHP() == 4 );
        REQUIRE( c.getCurrentHP() == 4 );
        REQUIRE( c.getName().compare("Standard") == 0 );
        for (Stat stat : statArray)
        {
            REQUIRE( c.getStatScore(stat) == stats[stat] );
            REQUIRE( c.getStatModifier(stat) == modifiers[stat] );
        }
    }
}