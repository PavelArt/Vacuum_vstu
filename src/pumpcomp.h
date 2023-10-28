#pragma once

#include "Wire.h"
#include "GyverStepper.h"

class PumpComp {
    private:
        GStepper< STEPPER2WIRE >* stepper;
        int steps;
    public:
        PumpComp(GStepper< STEPPER2WIRE >* _STEPPER);
        void RunManual(int _speed);
        void StopManual();
        void RunMlManual(int _ml);
        bool tick();
        void SetSteps(int _steps);
        void SetSpeed(int _speed);
};