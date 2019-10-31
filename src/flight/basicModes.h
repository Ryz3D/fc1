#pragma once

#include "settings.h"
#include "flightMode.h"
#include "flight.h"
#include "rx.h"
#include "pwm.h"
#include "gyro.h"
#include "pid.h"
#include "mixer.h"

class FMAngle : public FlightMode {
    void init() override;
    void update() override;
};

class FMHorizon : public FlightMode {
    void init() override;
    void update() override;
};

class FMAcro : public FlightMode {
public:
    void init() override;
    void update() override;
private:
    PID pid_roll;
    PID pid_pitch;
    PID pid_yaw;

    float throttle;
    float sp_roll;
    float sp_pitch;
    float sp_yaw;
};

class FMTrainer : public FlightMode {
    void init() override;
    void update() override;
};
