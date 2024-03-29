#pragma once

#include <Arduino.h>
#include <string.h>

#define SETTING_COUNT 26
#define FORCE_DEFAULT 0

class Settings {
public:
    static void init();
    static bool exists(const char *key);
    static void set(const char *key, float value);
    static float get(const char *key);
    static void programMode();

    static const float f_default[SETTING_COUNT];
    static float EEMEM f_arr[SETTING_COUNT];
    static const char *s_arr[SETTING_COUNT];
private:
};
