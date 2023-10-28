#include "pressure.h"

Pressure::Pressure(byte _pin_clapan, byte _pin_pump) {
    this->pin_clapan = _pin_clapan;
    this->pin_pump = _pin_pump;
    pinMode(this->pin_clapan, OUTPUT);
    pinMode(this->pin_pump, OUTPUT);
    digitalWrite(this->pin_clapan, HIGH);
    digitalWrite(this->pin_pump, HIGH);
}

void Pressure::StartClapan() {
    digitalWrite(this->pin_clapan, LOW);
}

void Pressure::StopClapan() {
    digitalWrite(this->pin_clapan, HIGH);
}

void Pressure::StartPump() {
    digitalWrite(this->pin_pump, LOW);
}

void Pressure::StopPump() {
    digitalWrite(this->pin_pump, HIGH);
}
