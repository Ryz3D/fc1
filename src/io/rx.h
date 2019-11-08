#pragma once

#include <Arduino.h>
#include "math.h"

#define RX_CHANNELS 4
#define RX_TIMEOUT 100000
#define RX_INVALID 0
#define RX_SW_MODE 3 // -1 if unused

class RX {
public:
    static void init();
    static void update();

    static float signals[RX_CHANNELS];
    static bool valid;
private:
};
