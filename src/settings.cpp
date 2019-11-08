#include "settings.h"

float Settings::f_arr[SETTING_COUNT];

const char *Settings::s_arr[SETTING_COUNT] = {
    // global
    "angle_pid_factor",
    "rate_pid_factor",

    // angle
    "angle_max_roll",
    "angle_max_pitch",
    "angle_rate_yaw",

    "angle_roll_p",
    "angle_roll_i",
    "angle_roll_d",

    "angle_pitch_p",
    "angle_pitch_i",
    "angle_pitch_d",

    "angle_yaw_p",
    "angle_yaw_i",
    "angle_yaw_d",

    // acro
    "acro_rate_roll",
    "acro_rate_pitch",
    "acro_rate_yaw",

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

const float Settings::f_default[SETTING_COUNT] = {
    // global
    0.0025f, // angle_pid_factor
    0.00001f, // rate_pid_factor

    // angle
    40.0f, // max_roll
    40.0f, // max_pitch
    10000.0f, // rate_yaw

    -7.0f, // roll_p
    0.0f, // roll_i
    -0.002f, // roll_d

    7.0f, // pitch_p
    0.0f, // pitch_i
    0.002f, // pitch_d

    7.0f, // yaw_p
    0.0f, // yaw_i
    0.002f, // yaw_d

    // acro
    -10000.0f, // rate_roll
    10000.0f, // rate_pitch
    10000.0f, // rate_yaw

    -7.0f, // roll_p
    0.0f, // roll_i
    -0.002f, // roll_d

    -7.0f, // pitch_p
    0.0f, // pitch_i
    -0.002f, // pitch_d

    7.0f, // yaw_p
    0.0f, // yaw_i
    0.002f, // yaw_d
};

void Settings::init() {
    while (!eeprom_is_ready());
    for (uint8_t i = 0; i < SETTING_COUNT; i++) {
        eeprom_update_float(&f_arr[i], f_default[i]);
    }
}

void Settings::set(const char *key, float value) {
    while (!eeprom_is_ready());
    for (uint16_t i = 0; i < SETTING_COUNT; i++) {
        if (strcmp(s_arr[i], key) == 0) {
            eeprom_update_float(&f_arr[i], value);
        }
    }
}

float Settings::get(const char *key) {
    while (!eeprom_is_ready());
    for (uint16_t i = 0; i < SETTING_COUNT; i++) {
        if (strcmp(s_arr[i], key) == 0) {
            return eeprom_read_float(&f_arr[i]);
        }
    }
    return 0;
}

void Settings::programMode() {
    Serial.println(F("\\"));

    while (true) {
        if (Serial.available()) {
            String key = Serial.readStringUntil('=');
            if (key.startsWith("quit") == 0) {
                break;
            }

            float value = Serial.parseFloat();
            Serial.print("+");

            for (uint16_t i = 0; i < SETTING_COUNT; i++) {
                if (key.compareTo(s_arr[i]) == 0) {
                    eeprom_update_float(&f_arr[i], value);
                    Serial.print(F("+"));
                }
            }
            Serial.print(F("\n"));
        }
    }

    Serial.println(F("/"));
}
