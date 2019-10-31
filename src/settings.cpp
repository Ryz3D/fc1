#include "settings.h"

float Settings::f_arr[SETTING_COUNT] EEMEM = {
    -10000.0f, // acro_rate_roll
    10000.0f, // acro_rate_pitch
    10000.0f, // acro_rate_yaw

    0.00001f, // acro_pid_factor

    -7.0f, // acro_roll_p
    0.0f, // acro_roll_i
    -0.002f, // acro_roll_d

    -7.0f, // acro_pitch_p
    0.0f, // acro_pitch_i
    -0.002f, // acro_pitch_d

    7.0f, // acro_yaw_p
    0.0f, // acro_yaw_i
    0.002f, // acro_yaw_d
};

String Settings::s_arr[SETTING_COUNT] = {
    "acro_rate_roll",
    "acro_rate_pitch",
    "acro_rate_yaw",

    "acro_pid_factor",

    "acro_roll_p",
    "acro_roll_i",
    "acro_roll_d",

    "acro_pitch_p",
    "acro_pitch_i",
    "acro_pitch_d",

    "acro_yaw_p",
    "acro_yaw_i",
    "acro_yaw_d",
};

void Settings::init() {
    if (eeprom_read_byte(0) == SETTING_COUNT) {
        for (uint16_t i = 0; i < SETTING_COUNT; i++) {
            f_arr[i] = eeprom_read_float(&f_arr[1 + i]);
        }
    }

    for (uint16_t i = 0; i < SETTING_COUNT; i++) {
        eeprom_write_float(&f_arr[1 + i], f_arr[i]);
    }
}

float Settings::get(String key) {
    for (uint16_t i = 0; i < SETTING_COUNT; i++) {
        if (s_arr[i] == key) {
            return f_arr[i];
        }
    }
    return 0;
}

void Settings::programMode() {
    char c;
    String key;
    while ((c = Serial.read()) != '=' && Serial.available()) {
        key += c;
    }
    if (c == '=') {
        float value = Serial.parseFloat();
        for (uint16_t i = 0; i < SETTING_COUNT; i++) {
            if (s_arr[i] == key) {
                eeprom_update_float(&f_arr[1 + i], value);
            }
        }
    }
}
