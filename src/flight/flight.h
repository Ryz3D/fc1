#pragma once

#include <Arduino.h>

#include "io/info.h"
#include "io/sensors.h"
#include "flight/flightMode.h"
#include "flight/basicModes.h"

#if (AUTO_MODES == 1)
#include "flight/autoModes.h"
#define MODE_COUNT 7
#else
#define MODE_COUNT 4
#endif

#define MODE_DEFAULT 2

class Flight {
public:
    static void init();
    static void update();

    static FlightMode *modes[];
    static uint8_t currentMode;
private:
};
