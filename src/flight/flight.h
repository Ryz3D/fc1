#pragma once

#include <Arduino.h>
#include "sensors.h"
#include "flightMode.h"

#include "basicModes.h"

#if (AUTO_MODES == 1)
#include "autoModes.h"
#define MODE_COUNT 7
#else
#define MODE_COUNT 4
#endif

class Flight {
public:
    static void init();
    static void update();

    static FlightMode *modes[];
    static uint8_t currentMode;
private:
};
