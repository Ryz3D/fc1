#include "flight.h"

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
    currentMode = 0;
    for (uint8_t i = 0; i < MODE_COUNT; i++) {
        modes[i]->init();
    }
}

void Flight::update() {
    modes[currentMode]->update();
}
