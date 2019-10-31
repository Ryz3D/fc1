#include "pid.h"

void PID::update(float error) {
    sumError += error;

    pOut = pGain * error;
    iOut = iGain * sumError;
    dOut = dGain * (error - lastError);
    sumOut = pOut + iOut + dOut;

    lastError = error;
}

void PID::reset() {
    sumError = 0;
    lastError = 0;
    pOut = iOut = dOut = sumOut = 0;
}
