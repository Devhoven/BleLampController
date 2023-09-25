#pragma once
#include <Arduino.h>
#include "Definitions.h"
#include "Phase.h"

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
