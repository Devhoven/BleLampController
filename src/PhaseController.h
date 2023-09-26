#pragma once
#include <Arduino.h>
#include "Definitions.h"
#include "Phase.h"

// Controls at what time of the day the lamp is going to be turned on and off
namespace PhaseController
{
    enum Days
    {
        Monday,
        Tuesday,
        Wednesday,
        Thuresday,
        Friday,
        Saturday,
        Sunday,
        Count
    };

    // Keeps track of the current day
    extern Days CurrentDay;

    // Keeps track of the current time
    extern time CurrentTime;

    void Init();

    void Loop();
}
