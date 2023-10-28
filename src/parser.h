#pragma once

#include "servos.h"

#define PARS_SERVO_A_SET_START_POS 0x01
#define PARS_SERVO_A_SET_END_POS 0x02
#define PARS_SERVO_A_SET_SPEED 0x03
#define PARS_SERVO_A_SET_ACCEL 0x04
#define PARS_SERVO_A_SET_MIN_PWM 0x05
#define PARS_SERVO_A_SET_MAX_PWM 0x06
#define PARS_SERVO_A_TO_START 0x07
#define PARS_SERVO_A_TO_END 0x08
#define PARS_SERVO_A_TO_POS 0x09
#define PARS_SERVO_A_INIT 0x0A

#define PARS_SERVO_B_SET_START_POS 0x0B
#define PARS_SERVO_B_SET_END_POS 0x0C
#define PARS_SERVO_B_SET_SPEED 0x0D
#define PARS_SERVO_B_SET_ACCEL 0x0E
#define PARS_SERVO_B_SET_MIN_PWM 0x0F
#define PARS_SERVO_B_SET_MAX_PWM 0x10
#define PARS_SERVO_B_TO_START 0x11
#define PARS_SERVO_B_TO_END 0x12
#define PARS_SERVO_B_TO_POS 0x13
#define PARS_SERVO_B_INIT 0x14


class Parser {
    private:
        Servos* servo_a;
        Servos* servo_b;

    public:
        Parser(Servos* servo_up, Servos* servo_down);
        void parse(byte buffer[50], size_t length);
};