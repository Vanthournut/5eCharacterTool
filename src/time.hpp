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
