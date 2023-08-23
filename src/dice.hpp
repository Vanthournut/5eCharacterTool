#include <math.h>

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