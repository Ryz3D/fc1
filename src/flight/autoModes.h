#pragma once

class FMAltHold : public FlightMode {
    void init() {
        name = "Altitude Hold";
        valid = 1;
        sensors = SENSOR_ACC | SENSOR_GYRO | SENSOR_BARO;
    }

    void update() {
    }
};

class FMReturn : public FlightMode {
    void init() {
        name = "RTH";
        valid = 1;
        sensors = SENSOR_ACC | SENSOR_GYRO | SENSOR_BARO | SENSOR_GPS;
    }

    void update() {
    }
};

class FMLoiter : public FlightMode {
    void init() {
        name = "Loiter";
        valid = 1;
        sensors = SENSOR_ACC | SENSOR_GYRO | SENSOR_BARO | SENSOR_GPS;
    }

    void update() {
    }
};
