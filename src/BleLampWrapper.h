#pragma once
#include "Definitions.h"

#ifdef USE_LED
#define LED_BUILTIN 2
#endif

namespace BleLampWrapper
{
    extern bool DeviceConnected;
    
    extern ushort Brightness;

    void Init();
    
    // "brightness" ranges from 0 to 100
    void SetBrightness(ushort brightness);

    void Flicker();

    void FadeOut();
}