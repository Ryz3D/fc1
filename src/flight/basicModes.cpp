#include "flight/basicModes.h"

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

    pid_roll.pGain = Settings::get("acro_roll_p");
    pid_roll.iGain = Settings::get("acro_roll_i");
    pid_roll.dGain = Settings::get("acro_roll_d");

    pid_pitch.pGain = Settings::get("acro_pitch_p");
    pid_pitch.iGain = Settings::get("acro_pitch_i");
    pid_pitch.dGain = Settings::get("acro_pitch_d");

    pid_yaw.pGain = Settings::get("acro_yaw_p");
    pid_yaw.iGain = Settings::get("acro_yaw_i");
    pid_yaw.dGain = Settings::get("acro_yaw_d");

    rate_r = Settings::get("acro_rate_roll");
    rate_p = Settings::get("acro_rate_pitch");
    rate_y = Settings::get("acro_rate_yaw");

    pid_factor = Settings::get("pid_factor");
}

void FMAcro::update() {
    RX::update();
    Gyro::update();

    throttle = RX::signals[0];
    sp_roll =  RX::signals[1] * rate_r;
    sp_pitch = RX::signals[2] * rate_p;
    sp_yaw =   RX::signals[3] * rate_y;

    pid_roll.update(sp_roll - Gyro::g_roll);
    pid_pitch.update(sp_pitch - Gyro::g_pitch);
    pid_yaw.update(sp_yaw - Gyro::g_yaw);

    for (uint8_t i = 0; i < 4; i++) {
        float output = 0;
        output += throttle         * Mixer::mixer[i][0];
        output += pid_roll.sumOut  * Mixer::mixer[i][1] * pid_factor;
        output += pid_pitch.sumOut * Mixer::mixer[i][2] * pid_factor;
        output += pid_yaw.sumOut   * Mixer::mixer[i][3] * pid_factor;
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
