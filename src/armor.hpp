#pragma once

class Character;

enum ArmorType : char{
    Shield,
    LightArmor,
    MediumArmor,
    HeavyArmor,
    Clothing
};

class Armor {
    protected:
    ArmorType armorType;

    public:
    virtual char getArmorClass(const Character& character) = 0;
    ArmorType getType() {return armorType;};
};

class ArmorClassModifier {
    public:
    virtual char modifyArmorClass(const Character& character, char ac) = 0;
};

class ArmorClassCalculator {
    public:
    virtual char calculateArmorClass(const Character& character) = 0;

};

class Unarmored : public Armor{
    public:
    Unarmored() {armorType = Clothing;};
    char getArmorClass(const Character& character) override;
};