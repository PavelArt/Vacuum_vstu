#pragma once

#include "Arduino.h"

#define RUN_VACUUM 0x01
#define STOP_VACUUM 0x02

#define RUN_HEATER 0x03
#define STOP_HEATER 0x04

#define RUN_VALVE 0x05
#define STOP_VALVE 0x06

#define RUN_MIXER 0x07
#define STOP_MIXER 0x08


class Parser {
    private:
        Vacuum* vacuum;
        UpDown* updown;
        Mixer* mixer;
        Memory* memory;
        Cup* cup_a;
        Cup* cup_b;
        Display* display;
        Automode* automode;
        long pressure;
        long current_updown;
        long current_a_cup;
        long current_b_cup;
    public:
        Parser(Vacuum* _vacuum, UpDown* _updown, Mixer* _mixer, Cup* _cup_a, Cup* _cup_b, Memory* _memory, Display* _display, Automode* _automode);
        void parse(byte buffer[50], size_t length);
};