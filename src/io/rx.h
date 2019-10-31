#pragma once

#include <Arduino.h>
#include "math.h"

#define RX_CHANNELS 4
#define RX_TIMEOUT 100000
#define RX_INVALID 0

class RX {
public:
    static void init();
    static void update();

    static float signals[RX_CHANNELS];
private:
};
