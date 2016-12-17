#include <Arduino.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24Network_config.h>
#include <Sync.h>
#include <RF24Mesh.h>
#include <RF24Mesh_config.h>

#include "node_config.h"
#include "globals.h"
#include "analog_controls.h"
#include "buttons.h"
#include "NetInterface.h"
#include "MemoryFree.h"

void setup() {
    Serial.begin(115200);
    Net::setup();

    AnalogControls::setup();
    Buttons::setup();
    Serial.print("setup succeeded: ");
    Serial.println(freeMemory());
}

int lastFreeMemory = freeMemory();

void loop() {
    int newFreeMemory = freeMemory();
    if (newFreeMemory != lastFreeMemory) {
        Serial.print("Loop: ");
        Serial.println(newFreeMemory);
        lastFreeMemory = newFreeMemory;
    }

    Net::update();

    AnalogControls::check();
    //Buttons::check();
    delay(100);
    Net::receive();
}
