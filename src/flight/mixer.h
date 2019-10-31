#pragma once

#include <Arduino.h>

#define MIXER 2
// 0: nothin'
// 1: quad
// 2: plane (TAER)
// 3: plane (AETR)
// 4: elevon (TLR)

class Mixer {
public:
    static float mixer[4][4];
};
