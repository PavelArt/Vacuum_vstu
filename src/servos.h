#pragma once

#include "Wire.h"
#include <ServoSmooth.h>

class Servos {
    private:
        ServoSmooth* servo;
        byte pin;
        int start_pos;
        int end_pos;
        int speed;
        int accel;
        int pwn_min;
        int pwm_max;

    public:
        Servos(ServoSmooth* _servo, byte _pin, byte _start_pos, byte _end_pos, int _pwm_min, int _pwm_max); 
        void setStartPos(int _start_pos);
        void setEndPos(int _end_pos);
        void setSpeed(int speed);
        void setAccel(int accel);
        void setMinPWM(int _pwm);
        void setMaxPWM(int _pwm);
        void config();
        int getCurrent();
        void toStartPos();
        void toEndPos();
        void toPoint(int target);
        bool tick();
};