//
// Created by Patrick on 24.11.2016.
//
#include "Arduino.h"
#include "node_config.h"

#if AWAKER_NODE_ID == 10

//const byte analog_pins[] = {A0, A1, A2, A3, A4, A5};
const uint8_t analog_pins[] = {A0, A1};
const uint8_t analog_pin_count = arr_length(analog_pins);

uint16_t analog_last_values[analog_pin_count];
//alles mit 0 initialisieren
unsigned long analog_last_changes[analog_pin_count] = {0};

const uint8_t button_pins[] = {2, 3};

const uint8_t button_count = arr_length(button_pins);

//muss auf true stehen, da die internen pull-up-widerstände verwendet werden
bool button_pressed[button_count] = {true};

#elif AWAKER_NODE_ID == 11

#endif
