#include "Phase.h"

Phase::Phase(time activationTime, void (*phaseFunc)()) : ActivationTime{activationTime}, PhaseFunc{phaseFunc}
{}

void Phase::Activate()
{
    (*PhaseFunc)();
}