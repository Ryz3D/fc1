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
#if (FORCE_DEFAULT == 1)
    for (uint8_t i = 0; i < SETTING_COUNT; i++) {
        eeprom_update_float(&f_arr[i], f_default[i]);
    }
#endif
}

bool Settings::exists(const char *key) {
    while (!eeprom_is_ready());
    for (uint16_t i = 0; i < SETTING_COUNT; i++) {
        if (strcmp(s_arr[i], key) == 0) {
            return 1;
        }
    }
    return 0;
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
    Serial.print(F("\\\n"));

    bool progActive = 1;
    while (progActive) {
        if (Serial.available()) {
            String key = "";
            while (true) {
                int c = Serial.read();
                bool done = 0;

                switch (c) {
                    case '<':
                    {
                        float f = get(key.c_str());
                        if (exists(key.c_str())) {
                            Serial.print(f, 7);
                        }
                        else {
                            Serial.print("!");
                        }
                        Serial.print(F("\n"));
                        done = 1;
                        break;
                    }
                    case '>':
                    {
                        float value = Serial.parseFloat();
                        if (exists(key.c_str())) {
                            set(key.c_str(), value);
                            Serial.print(F("+"));
                        }
                        else {
                            Serial.print(F("!"));
                        }
                        Serial.print(F("\n"));
                        done = 1;
                        break;
                    }
                    case '!':
                    {
                        progActive = 0;
                        done = 1;
                        break;
                    }
                    default:
                    {
                        if (isAscii(c)) {
                            key.concat((char)c);
                        }
                        break;
                    }
                }
                
                if (done) {
                    break;
                }
            }
        }
    }

    Serial.print(F("/\n"));
}
