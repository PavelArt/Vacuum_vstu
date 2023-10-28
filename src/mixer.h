#pragma once

#include "Arduino.h"

class Mixer {
    public:
        Mixer(byte _pin);
        void StartMixer();
        void StopMixer();
        void SetTime(long time);
        void RunTime();
        bool tick();

    private:
        byte pin;
        bool is_tick;
        unsigned long stop_time;
        unsigned long need_time;
};