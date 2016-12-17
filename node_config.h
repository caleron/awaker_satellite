//
// Created by Patrick on 23.11.2016.
//
#ifndef AWAKER_SATELLITE_NODE_CONFIG_H
#define AWAKER_SATELLITE_NODE_CONFIG_H

#include "Arduino.h"
#include "globals.h"

//AWAKER_NODE soll die nodeId sein
#define AWAKER_NODE_ID 10
#define RADIO_CHANNEL 97

#define CS_PIN 9
#define CE_PIN 10
#define MESH_NOMASTER

/**
 * Array mit allen durch Potentiometer belegten Analogeingängen
 */
extern const uint8_t analog_pins[];
/**
 * Anzahl der belegten analogen Pins
 */
extern const uint8_t analog_pin_count;

/**
 * Array mit den letzten Werten am jeweiligen Analogeingang
 */
extern uint16_t analog_last_values[];
/**
 * Array mit den Zeiten der letzten Änderung am jeweiligen Analogeingang
 */
extern unsigned long analog_last_changes[];

/**
 * Anzahl angeschlossener Buttons
 */
extern const uint8_t button_count;

/**
 * Array mit den durch Buttons belegten IO-Ports
 */
extern const uint8_t button_pins[];

/**
 * Array mit letzten Zuständen der Buttons, damit ein Druck nur ein mal eine Nachricht auslöst
 */
extern bool button_pressed[];

#endif //AWAKER_SATELLITE_NODE_CONFIG_H
