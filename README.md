# BleLampController
 
This is an ESP32-based project, that uses BLE to control a Rollei Lumen Studio 150 studio light. 
The ESP32 is able to turn the light on and off at any specific time on any specific day of the week.
You can specify at which time the lamp should be turned on and off in the  [PhaseController.cpp](src/BleLamp/PhaseController.cpp) - file.
Be aware, that if you add or remove a phase, you have to update the `PhasesPerCount` - array as well.

[PhaseController.cpp](src/BleLamp/PhaseController.cpp):
```c++      
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
```

If you want to install the lamp controller, you need to compile and upload the given code with VS Code and Platformio to an ESP32. 

The ESP32 itself however, is not able to retreive the current time by itself.
It can only count up from the given time. 
Because of this you have to set the current time in the [PhaseController.cpp](src/BleLamp/PhaseController.cpp) - file to the current time (Time + Date).


[PhaseController.cpp](src/BleLamp/PhaseController.cpp)
```c++
// Keeps track of the current day
Days CurrentDay = Days::Friday;

// Keeps track of the current time
time CurrentTime = 8_h;
```

Finally, you need to figure out what the studio lamp's Mac address is and put it in `BLE_LAMP_MAC_ADDRESS` in [Definitions.h](src/Definitions.h):
```c++
#define BLE_LAMP_MAC_ADDRESS "XX:XX:XX:XX:XX:XX"
```