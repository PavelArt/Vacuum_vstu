#include "AccelStepper.h"
#include "GyverTimer.h"
#include "Servo.h"

#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.setTimeout()
}

void loop() {

}

void serialEvent() {
    byte buf[50];
    size_t buf_size = Serial.readBytesUntil(0xff, buf, 5);
}