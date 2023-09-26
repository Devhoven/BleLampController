#pragma once
#include "Definitions.h"

#ifdef USE_LED
#define LED_BUILTIN 2
#endif

// Handles all of the BLE-communication with the lamp and provides an easy interface to the lamp
namespace BleLampWrapper
{
    // Whether the controller is connected to the lamp
    extern bool DeviceConnected;
    
    // At what percentage the lamp is currently operating
    extern ushort Brightness;

    // Initializes the BLE-communication
    void Init();
    
    // "brightness" ranges from 0 to 100
    void SetBrightness(ushort brightness);

    // Flickers for a bit and turns the lamp on afterwards
    void FlickerOn();

    // Gradually turns the lamp off 
    void FadeOut();
}