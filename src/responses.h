#pragma once
#include "Wire.h"
#include "Arduino.h"

class Responses {
    public:
        static void answer(byte command, int value);
};