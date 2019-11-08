#include "io/rx.h"

float RX::signals[RX_CHANNELS];
bool RX::valid = 0;

uint64_t rising[RX_CHANNELS];
uint8_t pinLast[RX_CHANNELS];

ISR(PCINT0_vect) {
    uint64_t t = micros();

    for (uint8_t i = 0; i < RX_CHANNELS; i++) {
        if (pinLast[i] == 0 && PINB & (1 << i)) {
            pinLast[i] = 1;
            rising[i] = t;
        }
        else if (pinLast[i] == 1 && !(PINB & (1 << i))) {
            pinLast[i] = 0;
            RX::signals[i] = ((t - rising[i]) - 1500.0f) / 500.0f;
            RX::valid = 1;
        }
    }
}

void RX::init() {
    for (uint8_t i = 0; i < RX_CHANNELS; i++) {
        DDRB &= ~(1 << i);
    }

    PCMSK0 = 0xFF;
    PCICR |= (1 << PCIE0);

    for (uint8_t i = 0; i < RX_CHANNELS; i++) {
        RX::signals[i] = RX_INVALID;
    }
}

void RX::update() {
    if (micros() - rising[0] > RX_TIMEOUT) {
        for (uint8_t i = 0; i < RX_CHANNELS; i++) {
            RX::signals[i] = RX_INVALID;
            valid = 0;
        }
    }
}
