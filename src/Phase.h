#pragma once
#include "Definitions.h"

class Phase
{
    public: 
    time ActivationTime;

    public:
    Phase() = default;
    Phase(time activationTime, void (*phaseFunc)());

    void Activate();

    private:
    void (*PhaseFunc)();
};