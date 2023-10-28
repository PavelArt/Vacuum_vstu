#include "Arduino.h"
#include "GyverTimer.h"
#include "servos.h"
#include "parser.h"
#include "config.h"


ServoSmooth servo_smooth_a; 
ServoSmooth servo_smooth_b;

Servos servo_a(&servo_smooth_a, BASE_A_PIN, BASE_A_START_POS, BASE_A_END_POS, BASE_A_MIN_PWM, BASE_A_MAX_PWM);
Servos servo_b(&servo_smooth_b, BASE_B_PIN, BASE_B_START_POS, BASE_B_END_POS, BASE_B_MIN_PWM, BASE_B_MAX_PWM);

Parser parser(&servo_a, &servo_b);

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    servo_a.tick();
    servo_b.tick();
}

void serialEvent() {
    byte buf[50];
    size_t buf_size = Serial.readBytesUntil(0xff, buf, 5);
    parser.parse(buf, buf_size);
}