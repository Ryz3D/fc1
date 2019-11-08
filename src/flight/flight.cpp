#include "flight/flight.h"

// remember #define in flight.h
FlightMode *Flight::modes[] = {
    new FMAngle(),
    new FMHorizon(),
    new FMAcro(),
    new FMTrainer()
#if (AUTO_MODES == 1)
    new FMAltHold(),
    new FMReturn(),
    new FMLoiter()
#endif
};

uint8_t Flight::currentMode = 0;

void Flight::init() {
    currentMode = MODE_DEFAULT;
    modes[currentMode]->init();
}

void Flight::update() {
#if (RX_SW_MODE != -1)
    bool updated = 0;
    if (RX::signals[RX_SW_MODE] < -0.33f) {
        if (currentMode != 0) {
            currentMode = 0;
            updated = 1;
        }
    }
    else if (RX::signals[RX_SW_MODE] < 0.33f) {
        if (currentMode != 1) {
            currentMode = 1;
            updated = 1;
        }
    }
    else {
        if (currentMode != 2) {
            currentMode = 2;
            updated = 1;
        }
    }
    if (updated) {
        modes[currentMode]->init();
        Info::blink_short();
    }
#endif
    modes[currentMode]->update();
}
