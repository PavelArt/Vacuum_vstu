#include "responses.h"
#include "Arduino.h"

void Responses::answer(byte command, int value) {
    byte buffer[5];
    buffer[0] = command;
    buffer[1] = value & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = (value >> 16) & 0xFF;
    buffer[4] = 0xFF;
    Serial.write(buffer, 5);
}