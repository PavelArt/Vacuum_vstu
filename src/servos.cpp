#include "servos.h"

Servos::Servos(ServoSmooth* _servo, byte _pin, byte _start_pos, byte _end_pos, int _pwm_min, int _pwm_max) {
    this->servo = _servo;
    this->pin = _pin;
    this->start_pos = _start_pos;
    this->end_pos = _end_pos;
    this->pwn_min = _pwm_min;
    this->pwm_max = _pwm_max;
}

void Servos::toPoint(int _point) {
    this->servo->setTargetDeg(_point);
}

void Servos::config() {
    this->servo->detach();
    this->servo->setMaxAngle(170);
    this->servo->setAutoDetach(false);
    this->servo->attach(this->pin, this->pwn_min, this->pwm_max, this->start_pos);
}

bool Servos::tick() {
    return this->servo->tick();
}

int Servos::getCurrent() {
    return this->servo->getCurrentDeg();
}

void Servos::setStartPos(int _start_pos) {
    this->start_pos = _start_pos;
}

void Servos::setEndPos(int _end_pos) {
    this->end_pos = _end_pos;
}

void Servos::setSpeed(int _speed) {
    this->servo->setSpeed(_speed);
    this->speed = _speed;
}

void Servos::setAccel(int _accel) {
    this->servo->setAccel(_accel);
    this->accel = _accel;
}

void Servos::setMinPWM(int _pwm) {
    this->pwn_min = _pwm;
}

void Servos::setMaxPWM(int _pwm) {
    this->pwm_max = _pwm;
}

void Servos::toStartPos() {
    this->servo->setTargetDeg(this->start_pos);
    this->servo->tickManual();
}

void Servos::toEndPos() {
    this->servo->setTargetDeg(this->end_pos);
    this->servo->tickManual();
}


