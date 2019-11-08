#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "flight/flight.h"

#define MODE_ANGLE 0
#define MODE_HORIZON 1
#define MODE_ACRO 2
#if (AUTO_MODES == 1)
#define MODE_ALTHOLD 3
#define MODE_RTH 4
#define MODE_LOITER 5
#endif

class Gyro {
public:
    static void init();
    static void update();
    static void calibrate();

    static uint8_t address;
    static int temperature;
    static int16_t g_pitch, g_roll, g_yaw;
    static int16_t a_x, a_y, a_z, a_len;
    static double glp_p, glp_r, glp_y;
    static float a_pitch, a_roll;
    static float angle_p, angle_r;
private:
    static void write8(uint8_t addr, uint8_t value);
    static void initRead(uint8_t addr, uint8_t size);
    static int16_t read16();

    static bool calibrated;
    static int16_t g_axis[3], a_axis[3];
    static double g_cal[3], a_cal[3];
};
