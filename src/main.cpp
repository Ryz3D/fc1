/*
WIRING

Arduino Nano --- MPU-6050
VIN - VCC
GND - GND
A4  - SDA
A5  - SCL

MPU-6050 Y-Axis forward

Arduino Nano --- ESC/Servos
Channel Map see mixer.h
D2 - CH1
D3 - CH2
D6 - CH3
D7 - CH4

Arduino Nano --- RX
D8  - Throttle
D9  - Aileron
D10 - Elevator
D11 - Rudder
*/

#include "main.h"

void setup() {
  Serial.begin(9600);
  Info::init();
  Settings::init();

  delay(1000);

  Info::blink_long();
  Info::blink_long();
  Info::blink_long();

  for (uint16_t t = 0; t < 50; t++) {
    if (Serial.available()) {
      while (Serial.available()) Serial.read();
      Info::blink_short();
      Info::blink_short();
      Info::blink_short();
      Settings::programMode();
      break;
    }
    delay(100);
  }

  delay(100);

  Serial.flush();
  Serial.end();

  Flight::init();
  RX::init();
  PWM::init();
  Gyro::init();

  digitalWrite(LED_BUILTIN, HIGH);
  Gyro::calibrate();
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);

  Info::blink_long();
  Info::blink_short();
}

void loop() {
  Flight::update();
}
