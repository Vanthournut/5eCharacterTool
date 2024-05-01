#pragma once

enum TimeMeasurement : char {
    Action,
    BonusAction,
    Reaction,
    Minute,
    Hour,
    Day
};

struct TimeDuration
{
    TimeMeasurement measure;
    char quantity;
};

enum UpdateType : char {
    Refresh = 0,
    Round,
    Turn,
    ShortRest,
    LongRest,
    Dawn,
    Dusk
};