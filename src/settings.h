#pragma once

class Settings {
public:
    int32_t acro_rate_roll;
    int32_t acro_rate_pitch;
    int32_t acro_rate_yaw;

    int32_t acro_pid_factor;

    int32_t acro_roll_p;
    int32_t acro_roll_i;
    int32_t acro_roll_d;

    int32_t acro_pitch_p;
    int32_t acro_pitch_i;
    int32_t acro_pitch_d;

    int32_t acro_yaw_p;
    int32_t acro_yaw_i;
    int32_t acro_yaw_d;
private:
};

/*
#define ACRO_RATE_ROLL -10000
#define ACRO_RATE_PITCH 10000
#define ACRO_RATE_YAW 10000

#define ACRO_PID_FACTOR 0.00001

#define ACRO_ROLL_P -7.0
#define ACRO_ROLL_I -0.0
#define ACRO_ROLL_D -0.02

#define ACRO_PITCH_P 7.0
#define ACRO_PITCH_I 0.0
#define ACRO_PITCH_D 0.02

#define ACRO_YAW_P 3.0
#define ACRO_YAW_I 0.0
#define ACRO_YAW_D 0.02
*/
