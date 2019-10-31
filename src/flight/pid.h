#pragma once

class PID {
public:
    void update(float error);
    void reset();

    float pGain, iGain, dGain;
    float pOut, iOut, dOut, sumOut;
private:
    float sumError;
    float lastError;
};
