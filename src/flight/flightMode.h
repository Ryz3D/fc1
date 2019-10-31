#ifndef FLIGHTMODE_H
#define FLIGHTMODE_H

#include <Arduino.h>

class FlightMode {
public:
    virtual void init() = 0;
    virtual void update() = 0;

    String name;
    bool valid;
    uint8_t sensors;
};

#endif
