#pragma once
#include <Arduino.h>

// Has to be defined if the real bluetooth lamp is not in range
// If it is defined, the onboard led is going to be used as a replacement 
// #define USE_LED

// At what percentage of the maximum power the lamp should operate
#define OPERATION_BRIGHTNESS 33

// Time is given in microseconds
#define time int64_t
// 1h = 60min = 3600s = 3600000 milliseconds = 3600000000 microseconds
#define HOURS_TO_TIME 3600000000

time operator ""_h(unsigned long long);
time operator ""_h(long double);