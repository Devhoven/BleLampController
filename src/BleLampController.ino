#include <Arduino.h>
#include "PhaseController.h"

void setup() 
{
    Serial.begin(115200);
    Serial.println("Starting the BLE Lamp Controller");
   
    PhaseController::Init();
}

void loop() 
{ 
    PhaseController::Loop();
}