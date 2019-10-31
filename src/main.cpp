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
  //Serial.begin(9600);

  Flight::init();
  RX::init();
  PWM::init();
  Gyro::init();

  Flight::currentMode = MODE_ACRO;

  digitalWrite(LED_BUILTIN, HIGH);
  Gyro::calibrate();
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

void loop() {
  Flight::update();
}
