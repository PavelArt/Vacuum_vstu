#pragma once

#include "Arduino.h"

class Pressure {
    private:
        byte pin_clapan;
        byte pin_pump;

    public:
        Pressure(byte _pin_clapan, byte _pin_pump);
        void StartClapan();
        void StopClapan();
        void StartPump();
        void StopPump();
};