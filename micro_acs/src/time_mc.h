#ifndef TIME_MC_H
#define TIME_MC_H

#include <Arduino.h>

class TimeMC
{
public:
    unsigned long ms;

public:
    void update()
    {
        ms = millis();
    };
};

#endif