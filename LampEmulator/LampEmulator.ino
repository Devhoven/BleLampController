// BLE LAMP EMULATOR
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"

// Lamp BLE Service and Characteristic UUIDs
static BLEUUID ServiceUUID("0000ffc0-0000-1000-8000-00805f9b34fb");
static BLEUUID CharUUID("0000ffc1-0000-1000-8000-00805f9b34fb");

// Lamp Brightness
ushort Brightness = 0;

class LampServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        Serial.println("ESP32 is connected to the lamp.");
    }

    void onDisconnect(BLEServer *pServer)
    {
        Serial.println("ESP32 has disconnected from the lamp.");
    }
};

class LampCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 1)
        {
            Brightness = value[5];

            Serial.printf("Received Brightness: %d\n", Brightness);

            if (Brightness > 15)
                digitalWrite(2, HIGH);
            else
                digitalWrite(2, LOW);
        }
    }
};

void setup()
{
    Serial.begin(115200);

    pinMode(2, OUTPUT);

    BLEDevice::init("ESP32");

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new LampServerCallbacks());

    BLEService *pService = pServer->createService(ServiceUUID);

    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CharUUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    pCharacteristic->setValue(Brightness);

    pCharacteristic->setCallbacks(new LampCharacteristicCallbacks());

    BLEDescriptor pDescriptor = BLEDescriptor(BLEUUID((uint16_t)0x2902));
    pCharacteristic->addDescriptor(&pDescriptor);

    pService->start();

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    Serial.println("Lamp Emulator is ready!");

    const uint8_t *point = esp_bt_dev_get_address();

    for (int i = 0; i < 6; i++)
    {
        char str[3];

        sprintf(str, "%02X", (int)point[i]);
        Serial.print(str);

        if (i < 5)
        {
            Serial.print(":");
        }
    }
    Serial.println();
}

void loop()
{
    // You can add your custom logic here if needed.
    delay(1000);
}