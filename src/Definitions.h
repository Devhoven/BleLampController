#pragma once
#include <Arduino.h>

// For testing the code if the real lamp is not in range
// If it is defined, the onboard LED is used to indicate whether the real lamp is on or off
// #define USE_LED   

// The mac address of the lamp
#define BLE_LAMP_MAC_ADDRESS "A4:C1:38:16:0B:C5"

// At what percentage of the maximum power the lamp should operate
#define OPERATION_BRIGHTNESS 33

// Time is given in microseconds
#define time int64_t
// 1h = 60min = 3600s = 3600000 milliseconds = 3600000000 microseconds
#define HOURS_TO_TIME 3600000000

// Conversion operators, which convert hours into the used time unit
time operator""_h(unsigned long long);
time operator""_h(long double);