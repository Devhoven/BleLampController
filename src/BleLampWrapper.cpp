#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "BleLampWrapper.h"

namespace BleLampWrapper
{
    bool DeviceConnected = false;

    ushort Brightness = 0;

    #ifndef USE_LED
    class MyClientCallback: public BLEClientCallbacks 
    {
        void onConnect(BLEClient * pclient) 
        {
            BleLampWrapper::DeviceConnected = true;
            Serial.println("ESP32 is connected to the lamp.");
        }

        void onDisconnect(BLEClient * pclient) 
        {
            BleLampWrapper::DeviceConnected = false;
            Serial.println("ESP32 has disconnected from the lamp.");
        }
    };

    static BLEUUID ServiceUUID("0000ffc0-0000-1000-8000-00805f9b34fb");
    static BLEUUID CharUUID("0000ffc1-0000-1000-8000-00805f9b34fb");

    static BLEAddress* ServerAddress;
    static BLEClient* Client;
    static BLERemoteService* RemoteService;
    static BLERemoteCharacteristic* RemoteCharacteristic;

    uint8_t SetBrightnessMagicBits[] = {
        0x28, 0xff, 0xff, 0xff, 0x20, 0x38, 0x00, 0x0f, 0x29
    };
    #endif

    void Init()
    {
        #ifndef USE_LED
        BLEDevice::init("ESP32");

        ServerAddress = new BLEAddress("A4:C1:38:16:0B:C5");
        Client = BLEDevice::createClient();
        Client->setClientCallbacks(new MyClientCallback());

        // Connect to the remove BLE Server.
        Client->connect(*ServerAddress);

        // Obtain a reference to the service we are after in the remote BLE server.
        RemoteService = Client->getService(ServiceUUID);
        if (RemoteService == nullptr) 
        {
            Serial.print("Failed to find our service UUID: ");
            Serial.println(ServiceUUID.toString().c_str());
            return;
        }

        // Obtain a reference to the characteristic in the service of the remote BLE server.
        RemoteCharacteristic = RemoteService->getCharacteristic(CharUUID);
        if (RemoteCharacteristic == nullptr) 
        {
            Serial.print("Failed to find our characteristic UUID: ");
            Serial.println(CharUUID.toString().c_str());
            return;
        }

        while (!BleLampWrapper::DeviceConnected)
        {
            Client->connect(*ServerAddress);
            delay(500); // wait for 500ms before trying again
        }
        #endif

        #ifdef USE_LED
        pinMode(LED_BUILTIN, OUTPUT);
        #endif
    }

    // "brightness" ranges from 0 to 100
    void SetBrightness(ushort brightness)
    {
        if (brightness < 0 || brightness > 100)
            return;

        #ifndef USE_LED
        // The value for the brightness resides at index 5
        SetBrightnessMagicBits[5] = brightness;
        RemoteCharacteristic->writeValue(SetBrightnessMagicBits, sizeof(SetBrightnessMagicBits), true);
        BleLampWrapper::Brightness = brightness;
        #endif

        #ifdef USE_LED
        if (brightness < 15)
            digitalWrite(LED_BUILTIN, LOW);
        else
            digitalWrite(LED_BUILTIN, HIGH);   
        #endif
    }


    // Sets the brightness of the lamp to random values a few times and turns it on afterwards
    void Flicker()
    {
        for (int i = 0; i < 7; i++)
        {
            SetBrightness(random(30, 69));
            delay(random(40, 80));
            SetBrightness(0);
            delay(random(10, 30));
        }
        SetBrightness(OPERATION_BRIGHTNESS);
    }

    // Turns the lamp gradually off
    void FadeOut()
    {
        for (int i = BleLampWrapper::Brightness; i >= 0; i--)
        {
            BleLampWrapper::SetBrightness(i);
            delay(5);
        }
    }
}