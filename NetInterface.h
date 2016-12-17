//
// Created by Patrick on 24.11.2016.
//

#ifndef AWAKER_SATELLITE_NETINTERFACE_H
#define AWAKER_SATELLITE_NETINTERFACE_H

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include "node_config.h"

namespace Net {
    extern RF24 radio;
    extern RF24Network network;
    extern RF24Mesh mesh;

    void setup();

    void update();

    /**
     * Soll aufgerufen werden, wenn ein Potentiometer gedreht wird
     *
     * @param index der Index des Potentiometers
     * @param newValue der neue Wert als Zahl zwischen 0 und 255
     */
    void analog_changed(byte index, byte newValue);


    void button_pressed(byte index);

    /**
     * Sendet ein Paket an die Basis
     * @param data
     * @param msg_type
     * @param size
     */
    void send(const void *data, uint8_t msg_type, size_t size);

    void receive();

}
#endif //AWAKER_SATELLITE_NETINTERFACE_H
