#pragma once

#include <Arduino.h>

#include "settings.h"
#include "flight/flightMode.h"
#include "flight/flight.h"
#include "flight/pid.h"
#include "flight/mixer.h"
#include "io/rx.h"
#include "io/pwm.h"
#include "io/gyro.h"

class FMAngle : public FlightMode {
    void init() override;
    void update() override;
    PID pid_roll;
    PID pid_pitch;
    PID pid_yaw;

    float throttle;
    float sp_roll;
    float sp_pitch;
    float sp_yaw;

    float rate_r;
    float rate_p;
    float rate_y;
    
    float a_pid_factor;
    float r_pid_factor;
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

    float rate_r;
    float rate_p;
    float rate_y;
    
    float r_pid_factor;
};

class FMTrainer : public FlightMode {
    void init() override;
    void update() override;
};
