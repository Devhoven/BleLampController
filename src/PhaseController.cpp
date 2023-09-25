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
    time CurrentTime = 7.99_h;

    // Tracks the previous call to esp_timer_get_time(), in order to estimate the elapsed time
    time PreviousTime = 0;

    void TrackTime();

    void PrintTime()
    {
        Serial.print("Tag: ");
        Serial.print(CurrentDay);
        Serial.print(" Zeit: ");
        Serial.print(CurrentTime / (float)(HOURS_TO_TIME), 5);
        Serial.print(" PhaseIndex: ");
        Serial.print(CurrentPhaseIndex);
        Serial.print(" PhaseCount: ");
        Serial.println(PhasesPerDayCount[CurrentDay]);
    }

    void Init()
    {
        // Initializing the phase-array
        Phases = new Phase*[Days::Count];
        Phases[Days::Monday]    = new Phase[2] {{8_h,  BleLampWrapper::Flicker},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Tuesday]   = new Phase[2] {{8_h,  BleLampWrapper::Flicker},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Wednesday] = new Phase[2] {{8_h,  BleLampWrapper::Flicker},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Thuresday] = new Phase[2] {{8_h,  BleLampWrapper::Flicker},
                                                {20_h, BleLampWrapper::FadeOut}};
        Phases[Days::Friday]    = new Phase[2] {{8_h,  BleLampWrapper::Flicker},
                                                {12_h, BleLampWrapper::FadeOut}};
        Phases[Days::Saturday]  = new Phase[2] {{8_h,  BleLampWrapper::Flicker},
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

        if (CurrentPhaseIndex < PhasesPerDayCount[CurrentDay] &&
            CurrentTime >= Phases[CurrentDay][CurrentPhaseIndex].ActivationTime)
        {
            Phases[CurrentDay][CurrentPhaseIndex].Activate();
            CurrentPhaseIndex++;
        }
    }

    void TrackTime()
    {
        time currentTime = esp_timer_get_time();
        time elapsedTime = (currentTime - PreviousTime);
        PreviousTime = currentTime;

        CurrentTime += elapsedTime;

        PrintTime();

        if (CurrentTime >= 24_h)
        {
            CurrentTime = CurrentTime % (24_h);
            CurrentDay = (Days)((CurrentDay + 1) % Days::Count);
            CurrentPhaseIndex = 0;
        }
    }
}