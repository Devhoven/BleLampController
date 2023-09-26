#include <Arduino.h>
#include "PhaseController.h"
#include "BleLampWrapper.h"

namespace PhaseController
{
    // Pointer to an array which contains all the needed phases
    Phase** Phases = nullptr;
    // Saves how many phases each day has
    int* PhasesPerDayCount = nullptr;
    // Tracks which phase is the next one 
    uint CurrentPhaseIndex = 0;

    // Keeps track of the current day
    Days CurrentDay = Days::Friday;

    // Keeps track of the current time
    time CurrentTime = 8_h;

    // Tracks the previous call to esp_timer_get_time(), in order to estimate the elapsed time
    time PreviousTime = 0;

    void TrackTime();

    void Init()
    {
        // Initializing the phase-array
        Phases = new Phase*[Days::Count];
        Phases[Days::Monday]    = new Phase[2] {{8_h,  BleLampWrapper::FlickerOn},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Tuesday]   = new Phase[2] {{8_h,  BleLampWrapper::FlickerOn},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Wednesday] = new Phase[2] {{8_h,  BleLampWrapper::FlickerOn},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Thuresday] = new Phase[2] {{8_h,  BleLampWrapper::FlickerOn},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Friday]    = new Phase[2] {{8_h,  BleLampWrapper::FlickerOn},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Saturday]  = new Phase[2] {{8_h,  BleLampWrapper::FlickerOn},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Sunday]    = new Phase[0] {};
        
        PhasesPerDayCount = new int[Days::Count] {2, 2, 2, 2, 2, 2, 0};

        PreviousTime = esp_timer_get_time();

        BleLampWrapper::Init();
        BleLampWrapper::FadeOut();
    }

    void Loop()
    {
        TrackTime();

        // Checks whether there are phases left, and if there are, checks if the phase has to be activated
        if (CurrentPhaseIndex < PhasesPerDayCount[CurrentDay] &&
            CurrentTime >= Phases[CurrentDay][CurrentPhaseIndex].ActivationTime)
        {
            // If the time for the phase has come, its assigned function is called
            Phases[CurrentDay][CurrentPhaseIndex].Activate();
            CurrentPhaseIndex++;
        }
    }

    // Updates the "CurrentTime" and "CurrentDay" - variables 
    void TrackTime()
    {
        time currentTime = esp_timer_get_time();
        time elapsedTime = (currentTime - PreviousTime);
        PreviousTime = currentTime;

        CurrentTime += elapsedTime;

        // If a day has passed
        if (CurrentTime >= 24_h)
        {
            // The time get's reset
            CurrentTime = CurrentTime % (24_h);
            // The next day is counted
            CurrentDay = (Days)((CurrentDay + 1) % Days::Count);
            // The phase index get's reset
            CurrentPhaseIndex = 0;
        }
    }
}