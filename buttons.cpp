//
// Created by Patrick on 24.11.2016.
//

#include "buttons.h"
#include "node_config.h"
#include "Arduino.h"
#include "NetInterface.h"

namespace Buttons {
    /**
     * Setzt alle Button-Pins als Output
     */
    void setup() {
        for (byte i = 0; i < button_count; ++i) {
            pinMode(button_pins[i], INPUT);
            //evtl Input mit internem pull-up verwenden
            //pinMode(button_pins[i], INPUT_PULLUP);
        }
    }

    /**
     * Prüft, ob die Buttons gedrückt sind
     */
    void check() {
        byte val;
        for (byte i = 0; i < button_count; ++i) {
            val = digitalRead(button_pins[i]);

            if (val == HIGH && !button_pressed[i]) {
                //event auslösen
                Net::button_pressed(i);
                button_pressed[i] = true;
            } else if (val == LOW) {
                button_pressed[i] = false;
            }
        }
    }
}