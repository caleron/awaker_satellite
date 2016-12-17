//
// Created by Patrick on 23.11.2016.
//

#ifndef AWAKER_SATELLITE_ANALOG_CONTROLS_H
#define AWAKER_SATELLITE_ANALOG_CONTROLS_H

#include "node_config.h"
#include "NetInterface.h"

namespace AnalogControls {
    const uint8_t INITIAL_THRESHOLD = 30;
    const uint8_t TOLERANCE = 10;
    const uint16_t THRESHOLD_TIME = 2000;

    void setup();

    void check();
}

#endif //AWAKER_SATELLITE_ANALOG_CONTROLS_H
