#pragma once

#include <Arduino.h>

class Info {
public:
    static void init();
    static void blink_short();
    static void blink_medium();
    static void blink_long();
private:
};
