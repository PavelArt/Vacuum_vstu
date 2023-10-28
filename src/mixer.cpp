#include "mixer.h"

Mixer::Mixer(byte _pin) {
    this->pin = _pin;
    this->need_time = 1000;
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, HIGH);
    this->stop_time = 0;
}

void Mixer::StartMixer() {
    digitalWrite(this->pin, LOW);
}

void Mixer::StopMixer() {
    digitalWrite(this->pin, HIGH);
}

void Mixer::SetTime(long _time) {
    this->need_time = _time * 1000;
}

void Mixer::RunTime() {
    this->stop_time = millis() + this->need_time;
    this->StartMixer();
}

bool Mixer::tick() {
    if (millis() > this->stop_time) {
        this->StopMixer();
        return true;
    }
    return false;
}