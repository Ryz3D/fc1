#pragma once

#include <Arduino.h>

#define SETTING_COUNT 13

class Settings {
public:
    static void init();
    static float get(String key);
    static void programMode();

    static float f_arr[SETTING_COUNT] EEMEM;
    static String s_arr[SETTING_COUNT];
private:
};
