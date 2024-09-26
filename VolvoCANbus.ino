#include <Arduino.h>
#include <Streaming.h>

#include "src/canBus.h"
#include "src/linBus.h"
#include "src/linFrame.h"
#include "src/volvoState.h"

#define TX_PIN 9
#define RX_PIN 8

#define DEBUG 0

CanBus can(0x25);
LinBus lin(RX_PIN, TX_PIN);
VolvoState state;

bool validCoolantTemp, validOilTemp;
int coolantTemp, oilTemp;

void printTemps();

void setup() {
    Serial.begin(9600);
    // INIT LINBUS

    // INIT CANBUS
    can.init(CAN_250KBPS);
}

void loop() {
    // LINBUS
    lin.readBus();
    while (lin.frameAvailable()) {
        LinFrame frame = lin.popFrame();

        switch (frame.getID()) {
            case SWM_ID:
                state.updateStateSWM(frame.getResponse());
                break;
            case LSM_ID:
                state.updateStateLSM(frame.getResponse());
                break;
            default:
                if (DEBUG) {
                    Serial << "Header: " << _HEX ((uint8_t) frame.getHeader())
                        << " ID: " << _HEX (frame.getID())
                        << " response: ";
                    frame.printResponse();
                    Serial << endl;
                }
        }
    }

    // TODO CANBUS
    // validCoolantTemp = can.getCoolantTemp(&coolantTemp);
    // validOilTemp = can.getOilTemp(&oilTemp);

    //printTemps();
}

void printTemps() {
    Serial.print("Coolant temp: ");
    if(validCoolantTemp)
        Serial.print(coolantTemp);
    else
        Serial.print("--");
    Serial.print("°C\t\tOil temp: ");
    if(validOilTemp)
        Serial.print(oilTemp);
    else
        Serial.print("--");
    Serial.println("°C");
}
