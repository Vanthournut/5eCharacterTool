#pragma once
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
    OtherRollType
};

class DicePool {
    public:
    DicePool() {for(int i = 0; i < 7; i++){this->pool[i] = 0;}};
    DicePool(char pool[7]) {for(int i = 0; i < 7; i++){this->pool[i] = pool[i];}};
    char pool[7];
    std::string toString(){
        std::string output = "";
        
        // for (int i = 0; i < 7; i++)
        // {
        //     output += std::to_string((int) pool[i]);
        // }
        
        bool isEmpty = true;
        if (pool[6] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[6]) + "d20";
            isEmpty = false;
        }
        if (pool[5] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[5]) + "d12";
            isEmpty = false;
        }
        if (pool[4] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[4]) + "d10";
            isEmpty = false;
        }
        if (pool[3] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[3]) + "d8";
            isEmpty = false;
        }
        if (pool[2] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[2]) + "d6";
            isEmpty = false;
        }
        if (pool[1] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[1]) + "d4";
            isEmpty = false;
        }
        if (pool[0] != (char) 0)
        {
            if(!isEmpty) {
                output += '+';
            }
            output += std::to_string((int) pool[0]);
            isEmpty = false;
        }

        if(isEmpty) {
            output += "0";
        }

        return output;
    }

    friend DicePool operator+(DicePool p1, DicePool p2) {
        char pool[7] {0};
        for (char i = 0; i < 7; i++)
        {
            pool[i] = p1.pool[i] + p2.pool[i];
        }

        return DicePool(pool);
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