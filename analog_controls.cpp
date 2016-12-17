//
// Created by Patrick on 09.12.2016.
//

#include "analog_controls.h"
#include "MemoryFree.h"

namespace AnalogControls {
    void setup() {
        //startwerte lesen
        for (byte i = 0; i < analog_pin_count; ++i) {
            analog_last_values[i] = analogRead(analog_pins[i]);
        }
    }

    void check() {
        for (byte i = 0; i < analog_pin_count; ++i) {
//            Serial.print("Checking ctl ");
//            Serial.println(i);

            int newValue = analogRead(analog_pins[i]);
            int diff = newValue - analog_last_values[i];
            //muss in neuer Zeile gemacht werden, sonst bug
            diff = abs(diff);

            if (diff < TOLERANCE) {
                //Falls unter normaler Toleranz
//                Serial.print("diff of ctl ");
//                Serial.print(i);
//                Serial.print(" below tolerance (last value: ");
//                Serial.print(analog_last_values[i]);
//                Serial.print(", new value: ");
//                Serial.print(newValue);
//                Serial.print(", diff:");
//                Serial.print(diff);
//                Serial.println(")");
                continue;
            } else if (diff < INITIAL_THRESHOLD && analog_last_changes[i] + THRESHOLD_TIME < millis()) {
                //Falls unter Start-Toleranz und letzte Änderung länger als THRESHOLD_TIME ist
//                Serial.print("diff of ctl ");
//                Serial.print(i);
//                Serial.println(" below threshold tolerance and time");
                continue;
            }

            Serial.print("Analog Control ");
            Serial.print(i);
            Serial.print(" changed from ");
            Serial.print(analog_last_values[i]);
            Serial.print("  to ");
            Serial.println(newValue);

            //Änderung dokumentieren
            analog_last_changes[i] = millis();
            analog_last_values[i] = newValue;

            //auf Lichtskala herunterskalieren
            newValue = map(newValue, 0, 1023, 0, 255);

            //neuen Wert senden
            Net::analog_changed(i, newValue);
//            Serial.print("Free memory after reading ctl ");
//            Serial.print(i);
//            Serial.print(" : ");
//            Serial.println(freeMemory());
//            Serial.print("ctl ");
//            Serial.println(i);
//            Serial.println("checked");
        }
//        Serial.print("Free memory after check: ");
//        Serial.println(freeMemory());
    }
}
