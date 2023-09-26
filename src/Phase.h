#pragma once
#include "Definitions.h"

// Represents a phase, aka. at which time what function should be activated
class Phase
{
    public: 
    // The time when the assigned function should be called
    time ActivationTime;

    public:
    Phase() = default;
    Phase(time activationTime, void (*phaseFunc)());

    // Calls the assigned function
    void Activate();

    private:
    // The assigned function
    void (*PhaseFunc)();
};