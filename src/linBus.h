#ifndef LIN_BUS_H
#define LIN_BUS_H

#include <SoftwareSerial.h>
#include <Vector.h>

#include "linFrame.h"

#define SYNC_BYTE 0x55

class LinBus {
    SoftwareSerial *softSerial;

    Vector<char> bytes;

    Vector<LinFrame> frames;

public:
    LinBus();
    LinBus(int rxPin, int txPin);

    void readBus();
    bool frameAvailable();
    LinFrame popFrame();

private:
    void analizeBytes();
};

#endif  // LIN_BUS_H
