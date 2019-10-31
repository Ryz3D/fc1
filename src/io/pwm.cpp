#include "pwm.h"

Servo PWM::pwm[4];

void PWM::init() {
    pinMode(PIN_PWM0, OUTPUT);
    pinMode(PIN_PWM1, OUTPUT);
    pinMode(PIN_PWM2, OUTPUT);
    pinMode(PIN_PWM3, OUTPUT);

    pwm[0].attach(PIN_PWM0, 1000, 2000);
    pwm[1].attach(PIN_PWM1, 1000, 2000);
    pwm[2].attach(PIN_PWM2, 1000, 2000);
    pwm[3].attach(PIN_PWM3, 1000, 2000);
}

void PWM::writeFloat(uint8_t ch, float f) {
    pwm[ch].writeMicroseconds(constrain(f * 500 + 1500, 1000, 2000));
}
