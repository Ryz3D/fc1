#include "io/gyro.h"

uint8_t Gyro::address = 0x68;
int Gyro::temperature;
int16_t Gyro::g_pitch, Gyro::g_roll, Gyro::g_yaw;
int16_t Gyro::a_x, Gyro::a_y, Gyro::a_z, Gyro::a_len;
double Gyro::glp_p, Gyro::glp_r, Gyro::glp_y;
float Gyro::a_pitch, Gyro::a_roll;
float Gyro::angle_p, Gyro::angle_r;

bool Gyro::calibrated;
int16_t Gyro::g_axis[4], Gyro::a_axis[4];
double Gyro::g_cal[3];

void Gyro::write8(uint8_t addr, uint8_t value) {
    Wire.beginTransmission(address);
    Wire.write(addr);
    Wire.write(value);
    Wire.endTransmission();
}

void Gyro::initRead(uint8_t addr, uint8_t size) {
    Wire.beginTransmission(address);
    Wire.write(addr);
    Wire.endTransmission();
    Wire.requestFrom(address, size);
    while (Wire.available() < size);
}

int16_t Gyro::read16() {
    return Wire.read() << 8 | Wire.read();
}

void Gyro::init() {
    Wire.begin();
    TWBR = 0b00001100;
    write8(0x6B, 0x00); // activate
    write8(0x1B, 0x08); // 500dps full scale
    write8(0x1C, 0x10); // 8g full scale
    write8(0x1A, 0x03); // lpf 43hz
}

void Gyro::calibrate() {
    calibrated = false;
    for (uint16_t i = 0; i < 100; i++){
        update();
        for (uint8_t j = 0; j < 3; j++) {
            g_cal[j] += g_axis[j];
        }
        delay(10);
    }
    for (uint8_t i = 0; i < 3; i++) {
        g_cal[i] /= 2000;
    }
    calibrated = true;
}

void Gyro::update() {
    initRead(0x3B, 14);
    for (uint8_t i = 0; i < 3; i++) {
        a_axis[i] = read16();
    }
    temperature = read16();
    for (uint8_t i = 0; i < 3; i++) {
        g_axis[i] = read16();
    }

    uint8_t sensors = Flight::modes[Flight::currentMode]->sensors;

    if (sensors & SENSOR_GYRO) {
        if (calibrated) {
            for (uint8_t i = 0; i < 3; i++) {
                g_axis[i] -= g_cal[i];
            }
        }

        g_roll = g_axis[1];
        g_pitch = -g_axis[0];
        g_yaw = -g_axis[2];

        // 65.5 = 1°/s
        glp_r = (glp_r * 0.7) + ((g_roll / 65.5) * 0.3);
        glp_p = (glp_p * 0.7) + ((g_pitch / 65.5) * 0.3);
        glp_y = (glp_y * 0.7) + ((g_yaw / 65.5) * 0.3);
    }

    if (sensors & SENSOR_ACC) {
        a_x = a_axis[1];
        a_y = -a_axis[0];
        a_z = a_axis[2];

        // 1 / 250hz / 65.5
        angle_p += g_pitch * 0.0000611;
        angle_r += g_roll * 0.0000611;

        a_len = sqrt(a_x * a_x + a_y * a_y + a_z * a_z);
        if (abs(a_y) < a_len) {
            a_pitch = asin((float)a_y / a_len) * 57.296;
        }
        if (abs(a_x) < a_len) {
            a_roll = asin((float)a_x / a_len) * -57.296;
        }

        angle_p = angle_p * 0.9996 + a_pitch * 0.0004;
        angle_r = angle_r * 0.9996 + a_roll * 0.0004;
    }
}
