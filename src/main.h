#pragma once

#include <Arduino.h>

#include "settings.h"
#include "flight/mixer.h"
#include "flight/flight.h"
#include "io/rx.h"
#include "io/pwm.h"
#include "io/gyro.h"

#define AUTO_MODES 0 // alt_hold, rth, loiter

#define BLINK_SHORT digitalWrite(LED_BUILTIN, HIGH); \
    delay(50); \
    digitalWrite(LED_BUILTIN, LOW); \
    delay(50);

#define BLINK_LONG digitalWrite(LED_BUILTIN, HIGH); \
    delay(200); \
    digitalWrite(LED_BUILTIN, LOW); \
    delay(200);
