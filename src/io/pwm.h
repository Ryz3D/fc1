#pragma once

#define PIN_PWM0 2
#define PIN_PWM1 3
#define PIN_PWM2 6
#define PIN_PWM3 7

#include <Arduino.h>
#include <Servo.h>

class PWM {
public:
    static void init();
    static void writeFloat(uint8_t ch, float f);

    static Servo pwm[];
};
