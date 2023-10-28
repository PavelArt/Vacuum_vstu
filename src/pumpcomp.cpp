#include "pumpcomp.h"

PumpComp::PumpComp(GStepper< STEPPER2WIRE >* _stepper) {
    this->stepper = _stepper;
    this->stepper->setRunMode(FOLLOW_POS);
}

void PumpComp::RunManual(int _speed) {
    this->stepper->setSpeed(_speed);
    this->stepper->setRunMode(KEEP_SPEED);
}

void PumpComp::StopManual() {
    this->stepper->brake();
}

void PumpComp::RunMlManual(int _ml) {
    int steps = _ml * this->steps;
    this->stepper->setRunMode(FOLLOW_POS);
    this->stepper->setTarget(steps, RELATIVE);
}

void PumpComp::SetSteps(int _steps) {
    this->steps = _steps;
}

void PumpComp::SetSpeed(int _speed) {
    _speed = _speed * steps;
    this->stepper->setMaxSpeed(_speed);
    this->stepper->setAcceleration(0);
}

bool PumpComp::tick() {
    return this->stepper->tick();
}