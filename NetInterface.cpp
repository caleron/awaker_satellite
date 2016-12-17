//
// Created by Patrick on 24.11.2016.
//

#include "NetInterface.h"
#include "node_config.h"
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

namespace Net {
    RF24 radio(CS_PIN, CE_PIN);
    RF24Network network(radio);
    RF24Mesh mesh(radio, network);

    void radio_send(const void *data, uint8_t msg_type, size_t size);

    /**
     * Nachrichtentypen
     * typen 1-64 werden ohne ACK gesendet, 65-127 mit ACK. ACK ist etwa nicht notwendig, wenn eine Antwort erwartet wird
     */
    enum class MessageType : byte {
        ANALOG_CHANGE = 65,
        BUTTON_PUSHED = 66
    };

    /**
     * Struktur eines Paketes für Potentiometer
     */
    struct AnalogChangePackage {
        byte control_index;
        byte value;
    };

    void setup() {
        mesh.setNodeID(AWAKER_NODE_ID);
        mesh.begin(RADIO_CHANNEL);
    }

    void update() {
        mesh.update();
    }

    /**
     * Soll aufgerufen werden, wenn ein Potentiometer gedreht wird
     *
     * @param index der Index des Potentiometers
     * @param newValue der neue Wert als Zahl zwischen 0 und 255
     */
    void analog_changed(byte index, byte newValue) {
        AnalogChangePackage payload;
        payload.control_index = index;
        payload.value = newValue;

        byte type = static_cast<byte>(MessageType::ANALOG_CHANGE);

        send(&payload, type, sizeof(payload));
    }

    void button_pressed(byte index) {
        Serial.print("Button ");
        Serial.print(index);
        Serial.println(" pressed");

        //Payload ist nur der Button-Index
        byte payload = index;
        byte type = static_cast<byte>(MessageType::BUTTON_PUSHED);

        //send(&payload, type, sizeof(payload));
    }

    void send(const void *data, uint8_t msg_type, size_t size) {
        if (!mesh.write(data, msg_type, size)) {
            // If a write fails, check connectivity to the mesh network
            if (!mesh.checkConnection()) {
                //refresh the network address
                Serial.println("Renewing Address");
                mesh.renewAddress();
            } else {
                Serial.println("Send fail, Test OK");
            }
        } else {
            Serial.print("Send OK type ");
            Serial.println(msg_type);
        }
    }

    void receive() {
        while (network.available()) {
            RF24NetworkHeader header;

            MessageType type = static_cast<MessageType>(header.type);

            switch (type) {
                case MessageType::ANALOG_CHANGE:
                    AnalogChangePackage payload;
                    network.read(header, &payload, sizeof(payload));
                    Serial.print("Control ");
                    Serial.print(payload.control_index);
                    Serial.print(" changed to ");
                    Serial.println(payload.value);
                    break;
            }
        }
    }
}