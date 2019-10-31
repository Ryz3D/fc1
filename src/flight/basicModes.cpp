#include "basicModes.h"

void FMAngle::init() {
    name = "Angle";
    valid = 1;
    sensors = SENSOR_ACC | SENSOR_GYRO;
}

void FMAngle::update() {
}

void FMHorizon::init() {
    name = "Horizon";
    valid = 1;
    sensors = SENSOR_ACC | SENSOR_GYRO;
}

void FMHorizon::update() {
}

void FMAcro::init() {
    name = "Acro";
    valid = 1;
    sensors = SENSOR_GYRO;

    pid_roll =  PID();
    pid_pitch = PID();
    pid_yaw =   PID();

    pid_roll.pGain = ACRO_ROLL_P;
    pid_roll.iGain = ACRO_ROLL_I;
    pid_roll.dGain = ACRO_ROLL_D;

    pid_pitch.pGain = ACRO_PITCH_P;
    pid_pitch.iGain = ACRO_PITCH_I;
    pid_pitch.dGain = ACRO_PITCH_D;

    pid_yaw.pGain = ACRO_YAW_P;
    pid_yaw.iGain = ACRO_YAW_I;
    pid_yaw.dGain = ACRO_YAW_D;
}

void FMAcro::update() {
    RX::update();
    Gyro::update();

    throttle = RX::signals[0];
    sp_roll =  RX::signals[1] * ACRO_RATE_ROLL;
    sp_pitch = RX::signals[2] * ACRO_RATE_PITCH;
    sp_yaw =   RX::signals[3] * ACRO_RATE_YAW;

    pid_roll.update(sp_roll - Gyro::g_roll);
    pid_pitch.update(sp_pitch - Gyro::g_pitch);
    pid_yaw.update(sp_yaw - Gyro::g_yaw);

    for (uint8_t i = 0; i < 4; i++) {
        float output = 0;
        output += throttle         * Mixer::mixer[i][0];
        output += pid_roll.sumOut  * Mixer::mixer[i][1] * ACRO_PID_FACTOR;
        output += pid_pitch.sumOut * Mixer::mixer[i][2] * ACRO_PID_FACTOR;
        output += pid_yaw.sumOut   * Mixer::mixer[i][3] * ACRO_PID_FACTOR;
        PWM::writeFloat(i, output);
    }
}

void FMTrainer::init() {
    name = "Acro Trainer";
    valid = 1;
    sensors = SENSOR_ACC | SENSOR_GYRO;
}

void FMTrainer::update() {
}
