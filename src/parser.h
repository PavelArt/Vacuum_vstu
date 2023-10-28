#pragma once

#include "servos.h"
#include "pumpcomp.h"
#include "pressure.h"
#include "responses.h"
#include "mixer.h"

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

#define PARS_SERVO_A_ON_THE_MOVE 0x15
#define PARS_SERVO_B_ON_THE_MOVE 0x16

#define PARS_PUMP_A_START 0x17
#define PARS_PUMP_A_STOP 0x18
#define PARS_PUMP_A_SET_SPEED 0x19
#define PARS_PUMP_A_SET_STEPS 0x1A

#define PARS_PUMP_B_START 0x1B
#define PARS_PUMP_B_STOP 0x1C
#define PARS_PUMP_B_SET_SPEED 0x1D
#define PARS_PUMP_B_SET_STEPS 0x1E

#define PARS_PRESSURE_START_PUMP 0x1F
#define PARS_PRESSURE_STOP_PUMP 0x20
#define PARS_PRESSURE_START_CLAPAN 0x21
#define PARS_PRESSURE_STOP_CLAPAN 0x22
#define PARS_PRESSURE_SET_TIME_PUMP 0x23
#define PARS_PRESSURE_SET_TIME_CLAPAN 0x24

#define PARS_MIXER_START 0x25
#define PARS_MIXER_STOP 0x26
#define PARS_MIXER_SET_TIME 0x27
#define PARS_MIXER_START_TIME 0x28


class Parser {
    private:
        Servos* servo_a;
        Servos* servo_b;
        PumpComp* pump_comp_a;
        PumpComp* pump_comp_b;
        Pressure* pressure;
        Mixer* mixer;

    public:
        Parser(Servos* servo_up, Servos* servo_down, PumpComp* pump_comp_a, PumpComp* pump_comp_b, Pressure* pressure, Mixer* mixer);
        void parse(byte buffer[50], size_t length);
};