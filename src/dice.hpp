#include <math.h>
#include <iostream>

enum Die {
    modifier = 0,
    d4,
    d6,
    d8,
    d10,
    d12,
    d20
};

static const float dieAverage[7] = {
    1,
    2.5,
    3.5,
    4.5,
    5.5,
    6.5,
    10.5
};

enum RollType {
    AbilityCheck,
    Attack,
    SavingThrow,
    Other
};

class DicePool {
    public:
    DicePool(char pool[7]);
    char pool[7];
    std::string toString(){
        std::string output;
        if (pool[6] != 0)
        {
            output += pool[6] + "d20";
        }
        if (pool[5] != 0)
        {
            output += pool[5] + "d12";
        }
        if (pool[4] != 0)
        {
            output += pool[4] + "d10";
        }
        if (pool[3] != 0)
        {
            output += pool[3] + "d8";
        }
        if (pool[2] != 0)
        {
            output += pool[2] + "d6";
        }
        if (pool[1] != 0)
        {
            output += pool[1] + "d4";
        }
        if (pool[0] != 0)
        {
            output += pool[0];
        }
        
    }

    friend DicePool operator+(DicePool p1, DicePool p2) {
        char pool[7];
        for (char i = 0; i < 7; i++)
        {
            pool[i] = p1.pool[i] + p2.pool[i];
        }

        return   DicePool(pool);
    };

    private:
    int Average() {
        float average;
        for(int i = 0; i < 7; i++) {
            average += pool[i]*dieAverage[i];
        }
        return floor(average);
    }
    
    
};